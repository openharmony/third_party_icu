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

cmake_minimum_required(VERSION 3.10)
project(icu72_dat_diff C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error -Wno-c++11-narrowing -D_INC_STRING_S -D_INC_WCHAR_S -D_SECIMP=// -D_STDIO_S_DEFINED -D_INC_STDIO_S -D_INC_STDLIB_S -D_INC_MEMORY_S")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -Wall -Wno-error -Wno-c++11-narrowing -DUPDATER_ENABLE -DOPENSSL_SUPPRESS_DEPRECATED -DCOMPILER_GNU=1")
message("==UPSTREAM_ROOT: ${UPSTREAM_ROOT}")
set(ICU_ROOT "${UPSTREAM_ROOT}/third_party/icu")
set(UPDATER_ROOT "${UPSTREAM_ROOT}/base/update/updater")
set(BOUNDS_CHECK_ROOT "${UPSTREAM_ROOT}/third_party/bounds_checking_function")
add_definitions(-DDIFF_PATCH_SDK)

# 头文件路径
set(INCLUDE_DIRS
    "${ICU_ROOT}/icu4c/source/common"
    "${ICU_ROOT}/icu4c/source/i18n"
    "${UPDATER_ROOT}/interfaces/kits/include"
    "${UPDATER_ROOT}/interfaces/kits/include/package"
    "${UPDATER_ROOT}/services/diffpatch/diff"
    "${UPDATER_ROOT}/services/diffpatch/patch"
    "${UPDATER_ROOT}/services/diffpatch/bzip2"
    "${UPDATER_ROOT}/services/diffpatch"
    "${UPDATER_ROOT}/services/include"
    "${UPDATER_ROOT}/services/include/package"
    "${UPDATER_ROOT}/services/include/patch"
    "${UPDATER_ROOT}/services/common"
    "${UPDATER_ROOT}/utils/include"
    "${UPSTREAM_ROOT}/third_party/bounds_checking_function/include"
    "${UPSTREAM_ROOT}/third_party/bounds_checking_function/src"
    "${UPDATER_ROOT}/services/package/pkg_verify"
    "${UPDATER_ROOT}/services/package/pkg_algorithm"
    "${UPDATER_ROOT}/services/package"
    "${UPDATER_ROOT}/services/package/pkg_manager"
    "${UPDATER_ROOT}/services/package/pkg_package"
    "${UPDATER_ROOT}/services/include/log"
    "${UPDATER_ROOT}/services/include/script"
)

foreach(dir ${INCLUDE_DIRS})
    include_directories(${dir})
endforeach()

# 源文件
set(SOURCES
    icu72_dat_diff.cpp
)
file(GLOB BOUNDS_CHECK_SRC_LIST "${BOUNDS_CHECK_ROOT}/src/*.c")
file(GLOB pkg_algorithm_LIST "${UPDATER_ROOT}/services/package/pkg_algorithm/*.cpp")
file(GLOB log_LIST "${UPDATER_ROOT}/services/log/*.cpp")
file(GLOB pkg_manager_LIST "${UPDATER_ROOT}/services/package/pkg_manager/*.cpp")
file(GLOB pkg_package_LIST "${UPDATER_ROOT}/services/package/pkg_package/*.cpp")
file(GLOB pkg_verify_LIST "${UPDATER_ROOT}/services/package/pkg_verify/*.cpp")
list(FILTER pkg_verify_LIST EXCLUDE REGEX ".*hash_data_verifier\\.cpp$")
file(GLOB diffpatch_LIST "${UPDATER_ROOT}/services/diffpatch/diff/*.cpp")

add_library(difflib SHARED
    ${UPDATER_ROOT}/services/diffpatch/bzip2/bzip2_adapter.cpp
    ${UPDATER_ROOT}/services/diffpatch/diffpatch.cpp
    ${diffpatch_LIST}
    ${log_LIST}
    ${pkg_algorithm_LIST}
    ${pkg_manager_LIST}
    ${pkg_package_LIST}
    ${pkg_verify_LIST}
    ${UPDATER_ROOT}/services/common/ring_buffer/ring_buffer.cpp
)

add_library(BoundsCheckLib STATIC
    ${BOUNDS_CHECK_SRC_LIST}
)

target_link_libraries(difflib PRIVATE BoundsCheckLib)

# 可执行文件
add_executable(icu72_dat_diff ${SOURCES})

# 链接库
target_link_libraries(icu72_dat_diff
    BoundsCheckLib
    difflib
    bz2
    lz4
    crypto
    z
    pthread
    dl
)

# 安装
install(TARGETS icu72_dat_diff DESTINATION bin)
