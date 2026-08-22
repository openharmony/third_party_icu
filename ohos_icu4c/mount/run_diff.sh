#!/bin/bash
# Copyright (c) 2026 Huawei Device Co., Ltd.
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

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_OUT_DIR="$1"
DIFF_OUT_DIR="$2"

SOURCE_ROOT="${SCRIPT_DIR}/../../../../"
BUILD_DIR="${SOURCE_ROOT}/${DIFF_OUT_DIR}/build"
cp "${SCRIPT_DIR}/CMakeLists.txt" "${SOURCE_ROOT}/${DIFF_OUT_DIR}/"
cp "${SCRIPT_DIR}/icu72_dat_diff.cpp" "${SOURCE_ROOT}/${DIFF_OUT_DIR}/"
echo "ROOT_OUT_DIR: $ROOT_OUT_DIR" >&2
echo "SOURCE_ROOT: $SOURCE_ROOT" >&2
if [ -z "$ROOT_OUT_DIR" ]; then
    echo "Usage: $0 <root_out_dir> <output_dir>" >&2
    exit 1
fi

ICU_OUT_DIR="${SOURCE_ROOT}/${ROOT_OUT_DIR}/thirdparty/icu/out"
ICU_OLD_DATA_DIR="${SOURCE_ROOT}/third_party/icu/ohos_icu4j/data/old"
CMAKE_COMPILER_PATH="${SOURCE_ROOT}/prebuilts/clang/ohos/linux-x86_64/llvm/bin"

echo "=========================================" >&2
echo "Building icu72_dat_diff" >&2
echo "SOURCE_ROOT: $SOURCE_ROOT" >&2
echo "ICU_OUT_DIR: $ICU_OUT_DIR" >&2
echo "ICU_OLD_DATA_DIR: $ICU_OLD_DATA_DIR" >&2
echo "BUILD_DIR: $BUILD_DIR" >&2
echo "DIFF_OUT_DIR: $DIFF_OUT_DIR" >&2
echo "=========================================" >&2

if [ -d "${BUILD_DIR}" ]; then
    rm -rf "${BUILD_DIR}"
fi
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

cmake .. -DUPSTREAM_ROOT="${SOURCE_ROOT}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_SYSTEM_PROCESSOR=x86_64 \
    -DCMAKE_C_COMPILER=${CMAKE_COMPILER_PATH}/clang \
    -DCMAKE_CXX_COMPILER=${CMAKE_COMPILER_PATH}/clang++

make -j$(nproc)

echo "">&2
echo "=========================================" >&2
echo "Running icu72_dat_diff to generate icudt72l.diff" >&2
echo "=========================================" >&2

cd "${BUILD_DIR}"
./icu72_dat_diff \
    "${ICU_OLD_DATA_DIR}/icudt72l.dat" \
    "${ICU_OUT_DIR}/icudt74l.dat" \
    "${SOURCE_ROOT}/${DIFF_OUT_DIR}/icudt72l.diff"

echo "">&2
echo "=========================================">&2
echo "Done! Output: ${OUTPUT_DIR}/icudt72l.diff">&2
echo "=========================================">&2
