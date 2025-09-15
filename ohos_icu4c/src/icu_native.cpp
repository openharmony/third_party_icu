/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <unicode/putil.h>
#include <unicode/uloc.h>
#include <unicode/uchar.h>
#include <unicode/ucpmap.h>
#include <unicode/uldnames.h>
#include <unicode/ulocdata.h>
#include <unicode/utypes.h>
#include <unicode/uvernum.h>
#include <unicode/uversion.h>
#include <unicode/utf.h>
#include <unicode/utf8.h>
#include <unicode/utf16.h>

/* Restore C api definition */
#undef u_charAge
#undef u_getUnicodeVersion
#undef uldn_open
#undef uldn_close
#undef uldn_getLocale
#undef uldn_getDialectHandling
#undef uldn_localeDisplayName
#undef uldn_languageDisplayName
#undef uldn_scriptDisplayName
#undef uldn_scriptCodeDisplayName
#undef uldn_regionDisplayName
#undef uldn_variantDisplayName
#undef uldn_keyDisplayName
#undef uldn_keyValueDisplayName
#undef uldn_openForContext
#undef uldn_getContext
#undef ulocdata_getCLDRVersion
#undef u_versionFromString
#undef u_versionFromUString
#undef u_versionToString
#undef u_getVersion
#undef utf8_back1SafeBody
#undef utf8_prevCharSafeBody

extern "C"
{
void u_charAge(UChar32 c, UVersionInfo versionArray)
{
    U_ICU_ENTRY_POINT_RENAME(u_charAge)(c, versionArray);
}
void u_getUnicodeVersion(UVersionInfo versionArray)
{
    U_ICU_ENTRY_POINT_RENAME(u_getUnicodeVersion)(versionArray);
}
ULocaleDisplayNames* uldn_open(const char *locale, UDialectHandling dialectHandling, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_open)(locale, dialectHandling, pErrorCode);
}
void uldn_close(ULocaleDisplayNames *ldn)
{
    U_ICU_ENTRY_POINT_RENAME(uldn_close)(ldn);
}
const char* uldn_getLocale(const ULocaleDisplayNames *ldn)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_getLocale)(ldn);
}
UDialectHandling uldn_getDialectHandling(const ULocaleDisplayNames *ldn)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_getDialectHandling)(ldn);
}
int32_t uldn_localeDisplayName(const ULocaleDisplayNames *ldn, const char *locale, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_localeDisplayName)(ldn, locale, result, maxResultSize, pErrorCode);
}
int32_t uldn_languageDisplayName(const ULocaleDisplayNames *ldn, const char *lang, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_languageDisplayName)(ldn, lang, result, maxResultSize, pErrorCode);
}
int32_t uldn_scriptDisplayName(const ULocaleDisplayNames *ldn, const char *script, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_scriptDisplayName)(ldn, script, result, maxResultSize, pErrorCode);
}
int32_t uldn_scriptCodeDisplayName(const ULocaleDisplayNames *ldn, UScriptCode scriptCode, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_scriptCodeDisplayName)(ldn,
        scriptCode, result, maxResultSize, pErrorCode);
}
int32_t uldn_regionDisplayName(const ULocaleDisplayNames *ldn, const char *region, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_regionDisplayName)(ldn, region, result, maxResultSize, pErrorCode);
}
int32_t uldn_variantDisplayName(const ULocaleDisplayNames *ldn, const char *variant, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_variantDisplayName)(ldn,
        variant, result, maxResultSize, pErrorCode);
}
int32_t uldn_keyDisplayName(const ULocaleDisplayNames *ldn, const char *key, UChar *result,
    int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_keyDisplayName)(ldn, key, result, maxResultSize, pErrorCode);
}
int32_t uldn_keyValueDisplayName(const ULocaleDisplayNames *ldn, const char *key, const char *value,
    UChar *result, int32_t maxResultSize, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_keyValueDisplayName)(ldn,
        key, value, result, maxResultSize, pErrorCode);
}
ULocaleDisplayNames* uldn_openForContext(const char *locale, UDisplayContext *contexts,
    int32_t length, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_openForContext)(locale, contexts, length, pErrorCode);
}
UDisplayContext uldn_getContext(const ULocaleDisplayNames *ldn, UDisplayContextType type,
    UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uldn_getContext)(ldn, type, pErrorCode);
}
void ulocdata_getCLDRVersion(UVersionInfo versionArray, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ulocdata_getCLDRVersion)(versionArray, status);
}
void u_versionFromString(UVersionInfo versionArray, const char *versionString)
{
    U_ICU_ENTRY_POINT_RENAME(u_versionFromString)(versionArray, versionString);
}
void u_versionFromUString(UVersionInfo versionArray, const UChar *versionString)
{
    U_ICU_ENTRY_POINT_RENAME(u_versionFromUString)(versionArray, versionString);
}
void u_versionToString(const UVersionInfo versionArray, char *versionString)
{
    U_ICU_ENTRY_POINT_RENAME(u_versionToString)(versionArray, versionString);
}
void u_getVersion(UVersionInfo versionArray)
{
    U_ICU_ENTRY_POINT_RENAME(u_getVersion)(versionArray);
}
int32_t utf8_back1SafeBody(const uint8_t *s, int32_t start, int32_t i)
{
    return U_ICU_ENTRY_POINT_RENAME(utf8_back1SafeBody)(s, start, i);
}
UChar32 utf8_prevCharSafeBody(const uint8_t *s, int32_t start, int32_t *pi, UChar32 c, UBool strict)
{
    return U_ICU_ENTRY_POINT_RENAME(utf8_prevCharSafeBody)(s, start, pi, c, strict);
}
}