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

def copy_content(src_file, dest_file, out_file):
    if os.path.exists(src_file):
        with open(src_file, 'r', encoding='utf-8') as f:
            src_content = f.read().splitlines()
    else:
        src_content = []
    
    with open(dest_file, 'r', encoding='utf-8') as f:
        if 'bo.txt' in src_file:
            dest_content = f.read().replace('root', 'bo').splitlines(True)
            print(src_file)
        else:
            dest_content = f.read().splitlines(True)

    data = ''
    for line in dest_content:
        data += line
        if ('units{' in line) or ('unitsNarrow{' in line) or ('unitsShort{' in line):
            for content in src_content:
                data = data + '        ' + content + '\n'

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
    os.makedirs(out_dir + '/unit/', exist_ok=True)

    files = ['/unit/en_001.txt', '/unit/root.txt', '/unit/ug.txt', '/unit/zh_Hant_HK.txt', '/unit/zh_Hant.txt', '/unit/zh.txt']
    for file in files:
        copy_content(args.ohos_src_dir + file, args.icu_src_dir + file, out_dir + file)

    copy_content(args.ohos_src_dir + '/unit/bo.txt', args.icu_src_dir + '/unit/root.txt', out_dir + '/unit/bo.txt')

    copy_file(args.ohos_src_dir + '/data_filter.json', out_dir + '/data_filter.json')

    

