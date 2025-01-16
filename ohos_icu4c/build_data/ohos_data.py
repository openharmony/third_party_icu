#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import json
import os
import stat


def generate_replace_data(data_filter, ohos_src_dir):
    if (not os.path.exists(os.path.join(ohos_src_dir, "unit")) or 
        not os.path.exists(os.path.join(ohos_src_dir, "misc"))):
        return
    
    data_filter["fileReplacements"] = dict()
    data_filter["fileReplacements"]["directory"] = "$FILTERS"
    data_filter["fileReplacements"]["replacements"] = []
    
    for unit_file in os.listdir(os.path.join(ohos_src_dir, "unit")):
        data_filter["fileReplacements"]["replacements"].append("unit/{}".format(unit_file))
    
    for misc_file in os.listdir(os.path.join(ohos_src_dir, "misc")):
        data_filter["fileReplacements"]["replacements"].append("misc/{}".format(misc_file))


def add_loacale_by_name(data_filter, key):
    if len(key) == 1 and key[0] == "all":
        return
    data_filter["localeFilter"] = dict()
    data_filter["localeFilter"]["filterType"] = "locale"
    data_filter["localeFilter"]["includeChildren"] = False
    data_filter["localeFilter"]["includelist"] = key


def add_features_by_name(feature_filter, name, key):
    if len(key) == 1 and key[0] == "all":
        return
    if len(key) == 0:
        feature_filter[name] = "exclude"
        return
    feature_filter[name] = dict()
    feature_filter[name]["whitelist"] = key


def parse_config_file(data_filter, ohos_src_dir):
    if not os.path.exists(os.path.join(ohos_src_dir, "config.json")):
        return
    
    with open(os.path.join(ohos_src_dir, "config.json"), 'r', encoding='utf-8') as f:
        config = json.load(f)
    
    add_loacale_by_name(data_filter, config["locale"])
    feature_filter = dict()
    for feature in config.keys():
        if feature == "locale":
            continue
        add_features_by_name(feature_filter, feature, config[feature])
    if len(feature_filter.keys()) != 0:
        data_filter["featureFilters"] = feature_filter


def generate_json_file(ohos_src_dir, out_file):
    if not os.path.exists(ohos_src_dir):
        return
    
    data_filter = dict()
    data_filter["strategy"] = "subtractive"
    generate_replace_data(data_filter, ohos_src_dir)
    parse_config_file(data_filter, ohos_src_dir)
    
    flags = os.O_WRONLY | os.O_CREAT
    mode = stat.S_IWUSR | stat.S_IRUSR
    with os.fdopen(os.open(out_file, flags, mode), 'w') as f:
        json.dump(data_filter, f, indent=4)


def add_content(data, src_content, prefix=''):
    if len(prefix) == 0:
        for content in src_content:
            data = data + '        ' + content + '\n'
    else:
        data = data + '    ' + prefix + '{' + '\n'
        for content in src_content:
            data = data + '        ' + content + '\n'
        data = data + '    }' + '\n'
    return data


def copy_content(src_file, dest_file, out_file):
    if not os.path.exists(src_file) or not os.path.exists(dest_file):
        return

    with open(src_file, 'r', encoding='utf-8') as f:
        src_content = f.read().splitlines()

    with open(dest_file, 'r', encoding='utf-8') as f:
        dest_content = f.read().splitlines(True)

    data = ''
    signal = 0
    for index, line in enumerate(dest_content):
        if (index == len(dest_content) - 1) and (signal != 3):
            if signal == 0:
                data = add_content(data, src_content, 'units')
                signal = 1
            if signal == 1:
                data = add_content(data, src_content, 'unitsNarrow')
                signal = 2
            if signal == 2:
                data = add_content(data, src_content, 'unitsShort')
            data += line
        elif ('unitsShort{' in line) or ('unitsShort:' in line):
            if signal == 0:
                data = add_content(data, src_content, 'units')
                signal = 1
            if signal == 1:
                data = add_content(data, src_content, 'unitsNarrow')
            data += line
            if 'unitsShort{' in line:
                data = add_content(data, src_content)
            signal = 3
        elif ('unitsNarrow{' in line) or ('unitsNarrow:' in line):
            if signal == 0:
                data = add_content(data, src_content, 'units')
            data += line
            if 'unitsNarrow{' in line:
                data = add_content(data, src_content)
            signal = 2
        elif ('units{' in line) or ('units:' in line):
            data += line
            if 'units{' in line:
                data = add_content(data, src_content)
            signal = 1
        else:
            data += line

    flags = os.O_WRONLY | os.O_CREAT
    mode = stat.S_IWUSR | stat.S_IRUSR
    with os.fdopen(os.open(out_file, flags, mode), 'w') as f:
        f.write(data)


def copy_file(src_file, dest_file):
    if not os.path.exists(src_file):
        return

    with open(src_file, 'r', encoding='utf-8') as f:
        data = f.read()

    flags = os.O_WRONLY | os.O_CREAT
    mode = stat.S_IWUSR | stat.S_IRUSR
    with os.fdopen(os.open(dest_file, flags, mode), 'w') as f:
        f.write(data)


def add_content_misc(src_file, dest_file, out_file):
    if not os.path.exists(src_file) or not os.path.exists(dest_file):
        return

    with open(src_file, 'r', encoding='utf-8') as f:
        src_content = f.read().splitlines()

    convert_units = []
    unit_quantities = []
    signal = 0
    for content in src_content:
        if "convertUnits:" in content:
            signal = 1
            continue
        if "unitQuantities:" in content:
            signal = 2
            continue
        if signal == 1:
            convert_units.append(content)
        if signal == 2:
            unit_quantities.append(content)

    with open(dest_file, 'r', encoding='utf-8') as f:
        dest_content = f.read().splitlines(True)
    
    data  = ''
    for line in dest_content:
        data += line
        if "convertUnits{" in line:
            for content in convert_units:
                data = "{}{}\n".format(data, content)
        if "unitQuantities{" in line:
            for content in unit_quantities:
                data = "{}{}\n".format(data, content)

    flags = os.O_WRONLY | os.O_CREAT
    mode = stat.S_IWUSR | stat.S_IRUSR
    with os.fdopen(os.open(out_file, flags, mode), 'w') as f:
        f.write(data)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--icu_src_dir', type=str)
    parser.add_argument('--ohos_src_dir', type=str)
    parser.add_argument('--out_dir', type=str)
    args = parser.parse_args()

    unit_path = 'unit'
    misc_path = 'misc'
    units_file = 'units.txt'
    filter_file = 'data_filter.json'
    out_dir = os.path.join(args.out_dir, 'out', 'temp')
    os.makedirs(os.path.join(out_dir, unit_path), exist_ok=True)
    os.makedirs(os.path.join(out_dir, misc_path), exist_ok=True)

    if os.path.exists(os.path.join(args.ohos_src_dir, unit_path)):
        for file in os.listdir(os.path.join(args.ohos_src_dir, unit_path)):
            copy_content(os.path.join(args.ohos_src_dir, unit_path, file),
                         os.path.join(args.icu_src_dir, unit_path, file),
                         os.path.join(out_dir, unit_path, file))
    
    add_content_misc(os.path.join(args.ohos_src_dir, misc_path, units_file),
                     os.path.join(args.icu_src_dir, misc_path, units_file),
                     os.path.join(out_dir, misc_path, units_file))
    generate_json_file(args.ohos_src_dir, os.path.join(out_dir, filter_file))
