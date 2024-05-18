/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifdef ICU_SUPPORT_DISTRO
#include <stdlib.h>
#endif
#include <sys/stat.h>
#include "distro_tzdata_loader.h"

namespace OHOS {
namespace Global {
namespace I18n {
const char *DistroTZDataLoader::ICU_TZDATA_PATH = "/system/etc/tzdata_distro/icu/icu_tzdata.dat";
const char *DistroTZDataLoader::DISTRO_TZDATA_PATH = "/system/etc/tzdata_distro/icu";
const char *DistroTZDataLoader::TZDATA_PATH = "/system/etc/icu_tzdata";
const char *DistroTZDataLoader::ICU_TIMEZONE_FILES_DIR = "ICU_TIMEZONE_FILES_DIR";

void DistroTZDataLoader::SetDistroTZDataPath()
{
#ifdef ICU_SUPPORT_DISTRO
    // if distro_tzdata_path is exist, use distro tzdata first
    if (CheckFileExist()) {
        setenv(ICU_TIMEZONE_FILES_DIR, DISTRO_TZDATA_PATH, 1);
    } else {
        setenv(ICU_TIMEZONE_FILES_DIR, TZDATA_PATH, 1);
    }
#endif
}

bool DistroTZDataLoader::CheckFileExist()
{
    struct stat s;
    if (stat(ICU_TZDATA_PATH, &s) != 0 || !(s.st_mode & S_IFREG)) {
        return false;
    }
    return true;
}
} // namespace I18n
} // namespace Global
} // namespace OHOS