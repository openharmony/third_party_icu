#!/bin/bash
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

set -e

echo "[ICUData]++++++++++++++++++Pkg icu data start.++++++++++++++++++++++"
date +%F' '%H:%M:%S
echo $@

script_path=$(cd $(dirname $0); pwd)

while getopts "o:b:v:f:h" arg;
do
    case "${arg}" in
        "o")
            out_put_root_path=${OPTARG}
        ;;
        "b")
            tool_bin_dir=${OPTARG}
        ;;
        "v")
            icu_dat_name=${OPTARG}
        ;;
        "f")
            icu_data_filter_dir=${OPTARG}
        ;;
        "h")
            exit 0
        ;;
    ?)
        echo "unkonw argument"
        exit 1
        ;;
    esac
done

script_path=$(cd $(dirname $0); pwd)
root_path="$script_path/../../../.."

if ! root_path=$(realpath "$root_path"); then
    echo "Cannot find real path for root_path '$root_path'."
    exit 1
fi

out_put_root_path="$root_path/$out_put_root_path"
tool_bin_dir="$root_path/$tool_bin_dir/thirdparty/icu"
icu_source_path="$root_path/third_party/icu/icu4c"
res_out_root_dir="$out_put_root_path/thirdparty/icu"
icu_data_filter_file="$script_path/$icu_data_filter_dir/data_filter.json"

rm -rf "$out_put_root_path/thirdparty/icu/out/*"

gen_icu_data() {
    
    # compile to res file
    PYTHONPATH=$icu_source_path/source/python python3 -m icutools.databuilder \
    --src_dir $icu_source_path/source/data \
    --include_uni_core_data \
    --seqmode sequential \
    --filter_file $icu_data_filter_file \
    --mode unix-exec \
    --tool_dir $tool_bin_dir \
    --out_dir $res_out_root_dir/out/build/$icu_dat_name \
    --tmp_dir $res_out_root_dir/out/tmp \
    
    # package to one dat file
    export LD_LIBRARY_PATH=$tool_bin_dir:$LD_LIBRARY_PATH
    $tool_bin_dir/pkgdata \
    -s $res_out_root_dir/out/build/$icu_dat_name \
    -T $res_out_root_dir/out/tmp -p $icu_dat_name \
    -d $res_out_root_dir/out \
    $res_out_root_dir/out/tmp/icudata.lst
}

if ! gen_icu_data; then
    echo "[ICUData] gen icudata res failed."
    exit 1
fi
echo "[ICUData] gen icudata res success."

exit 0
