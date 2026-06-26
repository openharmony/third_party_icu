/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <string>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
#ifdef UPDATER_ENABLE
#include "diff_patch/diff_patch_interface.h"
#endif
 
namespace {
    constexpr char DIFF_FILE_PATH[] = "/system/usr/ohos_icu_diff/icudt72l.diff";
    constexpr char BASE_FILE_PATH[] = "/system/usr/icu/icudt74l.dat";
    constexpr char RESTORE_TARGET_DIR[] = "/data/service/el1/public/i18n/icu";
    constexpr char RESTORE_TARGET_PATH[] = "/data/service/el1/public/i18n/icu/icudt72l.dat";
    constexpr char MOUNT_TARGET_PATH[] = "/system/usr/ohos_icu/icudt72l.dat";
    constexpr mode_t DIR_MODE = 0755;
    constexpr unsigned char DIFF_MAGIC[] = {0x42, 0x53, 0x44, 0x49, 0x46, 0x46, 0x34, 0x30}; // "BSDIFF40"
}
 
bool CreateDirectoryRecursive(const char* path, mode_t mode)
{
    if (mkdir(path, mode) == 0) {
        return true;
    }
    if (errno == EEXIST) {
        return true;
    }
    if (errno == ENOENT) {
        char* tmp = strdup(path);
        if (tmp == nullptr) {
            return false;
        }
        char* p = strrchr(tmp, '/');
        if (p != nullptr) {
            *p = '\0';
            if (CreateDirectoryRecursive(tmp, mode)) {
                free(tmp);
                return CreateDirectoryRecursive(path, mode);
            }
        }
        free(tmp);
        return false;
    }
    return false;
}
 
bool IsFileExists(const char* path)
{
    struct stat st;
    return (stat(path, &st) == 0);
}
 
bool IsDiffFileValid()
{
    FILE* fp = fopen(DIFF_FILE_PATH, "rb");
    if (fp == nullptr) {
        return false;
    }
 
    unsigned char magic[sizeof(DIFF_MAGIC)];
    size_t readLen = fread(magic, 1, sizeof(DIFF_MAGIC), fp);
    fclose(fp);
 
    if (readLen != sizeof(DIFF_MAGIC)) {
        return false;
    }
 
    if (memcmp(magic, DIFF_MAGIC, sizeof(DIFF_MAGIC)) != 0) {
        return false;
    }
 
    return true;
}
 
bool RestoreIcuData()
{
    if (IsFileExists(RESTORE_TARGET_PATH)) {
        return true;
    }
 
    if (!IsFileExists(BASE_FILE_PATH)) {
        return false;
    }
 
    if (!IsFileExists(DIFF_FILE_PATH)) {
        return false;
    }
 
    if (!IsDiffFileValid()) {
        return false;
    }
 
    if (!CreateDirectoryRecursive(RESTORE_TARGET_DIR, DIR_MODE)) {
        return false;
    }
 
#ifdef UPDATER_ENABLE
    int32_t result = Updater::ApplyPatch(DIFF_FILE_PATH, BASE_FILE_PATH, RESTORE_TARGET_PATH);
    if (result != 0) {
        return false;
    }
#else
    return false;
#endif
 
    if (!IsFileExists(RESTORE_TARGET_PATH)) {
        return false;
    }
 
    return true;
}
 
bool MountIcuData()
{
    printf("[ICU_MOUNT] MountIcuData start\n");
 
    if (!IsFileExists(RESTORE_TARGET_PATH)) {
        printf("[ICU_MOUNT] Restore target path does not exist: %s\n", RESTORE_TARGET_PATH);
        return false;
    }
    printf("[ICU_MOUNT] Restore target path exists: %s\n", RESTORE_TARGET_PATH);
 
    if (!CreateDirectoryRecursive("/system/usr/ohos_icu", DIR_MODE)) {
        printf("[ICU_MOUNT] Failed to create directory: /system/usr/ohos_icu\n");
        return false;
    }
    printf("[ICU_MOUNT] Directory created: /system/usr/ohos_icu\n");
 
    if (mount(RESTORE_TARGET_PATH, MOUNT_TARGET_PATH, nullptr, MS_BIND, nullptr) != 0) {
        printf("[ICU_MOUNT] mount failed, errno: %d\n", errno);
        return false;
    }
    printf("[ICU_MOUNT] mount success\n");
 
    return true;
}
 
int main(int argc, char* argv[])
{
    printf("[ICU_MOUNT] Start hmos_cust_icu_mount\n");
 
    if (!RestoreIcuData()) {
        printf("[ICU_MOUNT] RestoreIcuData failed\n");
        return EXIT_FAILURE;
    }
    printf("[ICU_MOUNT] RestoreIcuData success\n");
 
    if (!MountIcuData()) {
        printf("[ICU_MOUNT] MountIcuData failed\n");
        return EXIT_FAILURE;
    }
    printf("[ICU_MOUNT] MountIcuData success\n");
 
    printf("[ICU_MOUNT] hmos_cust_icu_mount completed successfully\n");
    return EXIT_SUCCESS;
}