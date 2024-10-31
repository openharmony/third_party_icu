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
import os


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
    if os.path.exists(src_file):
        with open(src_file, 'r', encoding='utf-8') as f:
            src_content = f.read().splitlines()
    else:
        src_content = []
    
    with open(dest_file, 'r', encoding='utf-8') as f:
        dest_content = f.read().splitlines(True)

    data = ''
    signal = 0
    for index in range(len(dest_content)):
        line = dest_content[index]
        
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


    with open(out_file, 'w', encoding='utf-8') as f:
        f.write(data)


def copy_file(src_file, dest_file):
    with open(src_file, 'r', encoding='utf-8') as f:
        data = f.read()

    with open(dest_file, 'w', encoding='utf-8') as f:
        f.write(data)


if __name__=='__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--icu_src_dir', type=str)
    parser.add_argument('--ohos_src_dir', type=str)
    parser.add_argument('--out_dir', type=str)
    args = parser.parse_args()
    
    out_dir = args.out_dir + '/out/temp/'
    unit_path = '/unit/'
    filter_file = '/data_filter.json'
    os.makedirs(out_dir + unit_path, exist_ok=True)

    for file in os.listdir(args.ohos_src_dir + unit_path):
        copy_content(args.ohos_src_dir + unit_path + file, 
                     args.icu_src_dir + unit_path + file, out_dir + unit_path + file)

    copy_file(args.ohos_src_dir + filter_file, out_dir + filter_file)
