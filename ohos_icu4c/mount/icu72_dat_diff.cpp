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
#include <sys/stat.h>
#include <unistd.h>
 
#ifdef UPDATER_ENABLE
#include "update_diff.h"
#endif
 
bool IsFileExists(const char* path)
{
    struct stat st;
    return (stat(path, &st) == 0);
}
 
void PrintUsage(const char* progName)
{
    fprintf(stderr, "Usage: %s <icu72_dat_path> <icu74_dat_path> <output_diff_path>\n", progName);
    fprintf(stderr, "\nGenerate bsdiff patch from icu72 to icu74 dat files.\n");
    fprintf(stderr, "\nArguments:\n");
    fprintf(stderr, "  icu72_dat_path    Path to icudt72l.dat (new file)\n");
    fprintf(stderr, "  icu74_dat_path    Path to icudt74l.dat (old file, base)\n");
    fprintf(stderr, "  output_diff_path  Path to output .diff file\n");
}
 
int main(int argc, char* argv[])
{
    if (argc != 4) {
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }
 
    const char* icu72Path = argv[1];
    const char* icu74Path = argv[2];
    const char* diffPath = argv[3];
 
    if (!IsFileExists(icu72Path)) {
        fprintf(stderr, "Error: icu72 dat file not found: %s\n", icu72Path);
        return EXIT_FAILURE;
    }
 
    if (!IsFileExists(icu74Path)) {
        fprintf(stderr, "Error: icu74 dat file not found: %s\n", icu74Path);
        return EXIT_FAILURE;
    }
 
    printf("Generating bsdiff patch...\n");
    printf("  Old file (base): %s\n", icu74Path);
    printf("  New file:        %s\n", icu72Path);
    printf("  Output diff:     %s\n", diffPath);
 
#ifdef UPDATER_ENABLE
    int32_t result = UpdatePatch::UpdateDiff::DiffBlock(icu74Path, icu72Path, diffPath);
    if (result != 0) {
        fprintf(stderr, "Error: Failed to generate patch, error code: %d\n", result);
        return EXIT_FAILURE;
    }
#else
    return EXIT_FAILURE;
#endif
 
    printf("Success: Patch generated at %s\n", diffPath);
    return EXIT_SUCCESS;
}