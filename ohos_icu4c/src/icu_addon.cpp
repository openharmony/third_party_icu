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

#include <unicode/ubidi.h>
#include <unicode/ubrk.h>
#include <unicode/ucal.h>
#include <unicode/uchar.h>
#include <unicode/ucnv.h>
#include <unicode/ucnv_err.h>
#include <unicode/ucol.h>
#include <unicode/udat.h>
#include <unicode/uenum.h>
#include <unicode/ufieldpositer.h>
#include <unicode/uidna.h>
#include <unicode/uloc.h>
#include <unicode/unorm2.h>
#include <unicode/unum.h>
#include <unicode/unumberformatter.h>
#include <unicode/uscript.h>
#include <unicode/uset.h>
#include <unicode/utrans.h>

#ifdef ICU_SUPPORT_LIBBEGETUTIL
#include "parameter.h"
#endif

#ifdef ICU_SUPPORT_LIBBEGETUTIL
bool g_isCustomLocale = false;
#endif
/* Restore C api definition */
#undef UCNV_TO_U_CALLBACK_ESCAPE
#undef u_charDigitValue
#undef u_charDirection
#undef u_charFromName
#undef u_charMirror
#undef u_charName
#undef u_charType
#undef u_digit
#undef u_enumCharNames
#undef u_enumCharTypes
#undef u_foldCase
#undef u_forDigit
#undef u_getBidiPairedBracket
#undef u_getBinaryPropertySet
#undef u_getCombiningClass
#undef u_getFC_NFKC_Closure
#undef u_getIntPropertyMaxValue
#undef u_getIntPropertyMinValue
#undef u_getIntPropertyValue
#undef u_getNumericValue
#undef u_getPropertyEnum
#undef u_getPropertyName
#undef u_getPropertyValueEnum
#undef u_getPropertyValueName
#undef u_hasBinaryProperty
#undef u_isIDIgnorable
#undef u_isIDPart
#undef u_isIDStart
#undef u_isISOControl
#undef u_isJavaIDPart
#undef u_isJavaIDStart
#undef u_isJavaSpaceChar
#undef u_isMirrored
#undef u_isUAlphabetic
#undef u_isULowercase
#undef u_isUUppercase
#undef u_isUWhiteSpace
#undef u_isWhitespace
#undef u_isalnum
#undef u_isalpha
#undef u_isbase
#undef u_isblank
#undef u_iscntrl
#undef u_isdefined
#undef u_isdigit
#undef u_isgraph
#undef u_islower
#undef u_isprint
#undef u_ispunct
#undef u_isspace
#undef u_istitle
#undef u_isupper
#undef u_isxdigit
#undef u_stringHasBinaryProperty
#undef u_tolower
#undef u_totitle
#undef u_toupper
#undef ubidi_close
#undef ubidi_countParagraphs
#undef ubidi_countRuns
#undef ubidi_getBaseDirection
#undef ubidi_getClassCallback
#undef ubidi_getCustomizedClass
#undef ubidi_getDirection
#undef ubidi_getLength
#undef ubidi_getLevelAt
#undef ubidi_getLevels
#undef ubidi_getLogicalIndex
#undef ubidi_getLogicalMap
#undef ubidi_getLogicalRun
#undef ubidi_getParaLevel
#undef ubidi_getParagraph
#undef ubidi_getParagraphByIndex
#undef ubidi_getProcessedLength
#undef ubidi_getReorderingMode
#undef ubidi_getReorderingOptions
#undef ubidi_getResultLength
#undef ubidi_getText
#undef ubidi_getVisualIndex
#undef ubidi_getVisualMap
#undef ubidi_getVisualRun
#undef ubidi_invertMap
#undef ubidi_isInverse
#undef ubidi_isOrderParagraphsLTR
#undef ubidi_open
#undef ubidi_openSized
#undef ubidi_orderParagraphsLTR
#undef ubidi_reorderLogical
#undef ubidi_reorderVisual
#undef ubidi_setClassCallback
#undef ubidi_setContext
#undef ubidi_setInverse
#undef ubidi_setLine
#undef ubidi_setPara
#undef ubidi_setReorderingMode
#undef ubidi_setReorderingOptions
#undef ubidi_writeReordered
#undef ubidi_writeReverse
#undef ublock_getCode
#undef ubrk_clone
#undef ubrk_close
#undef ubrk_countAvailable
#undef ubrk_current
#undef ubrk_first
#undef ubrk_following
#undef ubrk_getAvailable
#undef ubrk_getBinaryRules
#undef ubrk_getLocaleByType
#undef ubrk_getRuleStatus
#undef ubrk_getRuleStatusVec
#undef ubrk_isBoundary
#undef ubrk_last
#undef ubrk_next
#undef ubrk_open
#undef ubrk_openBinaryRules
#undef ubrk_openRules
#undef ubrk_preceding
#undef ubrk_previous
#undef ubrk_setText
#undef ucal_add
#undef ucal_clear
#undef ucal_clearField
#undef ucal_clone
#undef ucal_close
#undef ucal_countAvailable
#undef ucal_equivalentTo
#undef ucal_get
#undef ucal_getAttribute
#undef ucal_getAvailable
#undef ucal_getCanonicalTimeZoneID
#undef ucal_getDSTSavings
#undef ucal_getDayOfWeekType
#undef ucal_getDefaultTimeZone
#undef ucal_getFieldDifference
#undef ucal_getGregorianChange
#undef ucal_getHostTimeZone
#undef ucal_getKeywordValuesForLocale
#undef ucal_getLimit
#undef ucal_getLocaleByType
#undef ucal_getMillis
#undef ucal_getNow
#undef ucal_getTZDataVersion
#undef ucal_getTimeZoneDisplayName
#undef ucal_getTimeZoneID
#undef ucal_getTimeZoneIDForWindowsID
#undef ucal_getTimeZoneOffsetFromLocal
#undef ucal_getTimeZoneTransitionDate
#undef ucal_getType
#undef ucal_getWeekendTransition
#undef ucal_getWindowsTimeZoneID
#undef ucal_inDaylightTime
#undef ucal_isSet
#undef ucal_isWeekend
#undef ucal_open
#undef ucal_openCountryTimeZones
#undef ucal_openTimeZoneIDEnumeration
#undef ucal_openTimeZones
#undef ucal_roll
#undef ucal_set
#undef ucal_setAttribute
#undef ucal_setDate
#undef ucal_setDateTime
#undef ucal_setDefaultTimeZone
#undef ucal_setGregorianChange
#undef ucal_setMillis
#undef ucal_setTimeZone
#undef ucnv_clone
#undef ucnv_close
#undef ucnv_compareNames
#undef ucnv_convert
#undef ucnv_convertEx
#undef ucnv_countAliases
#undef ucnv_countAvailable
#undef ucnv_countStandards
#undef ucnv_detectUnicodeSignature
#undef ucnv_fixFileSeparator
#undef ucnv_flushCache
#undef ucnv_fromAlgorithmic
#undef ucnv_fromUChars
#undef ucnv_fromUCountPending
#undef ucnv_fromUnicode
#undef ucnv_getAlias
#undef ucnv_getAliases
#undef ucnv_getAvailableName
#undef ucnv_getCCSID
#undef ucnv_getCanonicalName
#undef ucnv_getDefaultName
#undef ucnv_getDisplayName
#undef ucnv_getFromUCallBack
#undef ucnv_getInvalidChars
#undef ucnv_getInvalidUChars
#undef ucnv_getMaxCharSize
#undef ucnv_getMinCharSize
#undef ucnv_getName
#undef ucnv_getNextUChar
#undef ucnv_getPlatform
#undef ucnv_getStandard
#undef ucnv_getStandardName
#undef ucnv_getStarters
#undef ucnv_getSubstChars
#undef ucnv_getToUCallBack
#undef ucnv_getType
#undef ucnv_isAmbiguous
#undef ucnv_isFixedWidth
#undef ucnv_open
#undef ucnv_openAllNames
#undef ucnv_openCCSID
#undef ucnv_openPackage
#undef ucnv_openStandardNames
#undef ucnv_openU
#undef ucnv_reset
#undef ucnv_resetFromUnicode
#undef ucnv_resetToUnicode
#undef ucnv_setDefaultName
#undef ucnv_setFallback
#undef ucnv_setFromUCallBack
#undef ucnv_setSubstChars
#undef ucnv_setSubstString
#undef ucnv_setToUCallBack
#undef ucnv_toAlgorithmic
#undef ucnv_toUChars
#undef ucnv_toUCountPending
#undef ucnv_toUnicode
#undef ucnv_usesFallback
#undef ucol_clone
#undef ucol_cloneBinary
#undef ucol_close
#undef ucol_countAvailable
#undef ucol_equal
#undef ucol_getAttribute
#undef ucol_getAvailable
#undef ucol_getBound
#undef ucol_getContractionsAndExpansions
#undef ucol_getDisplayName
#undef ucol_getEquivalentReorderCodes
#undef ucol_getFunctionalEquivalent
#undef ucol_getKeywordValues
#undef ucol_getKeywordValuesForLocale
#undef ucol_getKeywords
#undef ucol_getLocaleByType
#undef ucol_getMaxVariable
#undef ucol_getReorderCodes
#undef ucol_getRules
#undef ucol_getRulesEx
#undef ucol_getSortKey
#undef ucol_getStrength
#undef ucol_getTailoredSet
#undef ucol_getVariableTop
#undef ucol_greater
#undef ucol_greaterOrEqual
#undef ucol_mergeSortkeys
#undef ucol_open
#undef ucol_openAvailableLocales
#undef ucol_openBinary
#undef ucol_openRules
#undef ucol_setAttribute
#undef ucol_setMaxVariable
#undef ucol_setReorderCodes
#undef ucol_setStrength
#undef ucol_strcoll
#undef ucol_strcollUTF8
#undef udat_adoptNumberFormat
#undef udat_adoptNumberFormatForFields
#undef udat_applyPattern
#undef udat_clone
#undef udat_close
#undef udat_countAvailable
#undef udat_countSymbols
#undef udat_format
#undef udat_formatCalendar
#undef udat_formatCalendarForFields
#undef udat_formatForFields
#undef udat_get2DigitYearStart
#undef udat_getAvailable
#undef udat_getBooleanAttribute
#undef udat_getCalendar
#undef udat_getContext
#undef udat_getLocaleByType
#undef udat_getNumberFormat
#undef udat_getNumberFormatForField
#undef udat_getSymbols
#undef udat_isLenient
#undef udat_open
#undef udat_parse
#undef udat_parseCalendar
#undef udat_set2DigitYearStart
#undef udat_setBooleanAttribute
#undef udat_setCalendar
#undef udat_setContext
#undef udat_setLenient
#undef udat_setNumberFormat
#undef udat_setSymbols
#undef udat_toCalendarDateField
#undef udat_toPattern
#undef uenum_close
#undef uenum_count
#undef uenum_next
#undef uenum_reset
#undef uenum_unext
#undef ufieldpositer_close
#undef ufieldpositer_next
#undef ufieldpositer_open
#undef uidna_close
#undef uidna_labelToASCII
#undef uidna_labelToASCII_UTF8
#undef uidna_labelToUnicode
#undef uidna_labelToUnicodeUTF8
#undef uidna_nameToASCII
#undef uidna_nameToASCII_UTF8
#undef uidna_nameToUnicode
#undef uidna_nameToUnicodeUTF8
#undef uidna_openUTS46
#undef uloc_acceptLanguage
#undef uloc_acceptLanguageFromHTTP
#undef uloc_addLikelySubtags
#undef uloc_canonicalize
#undef uloc_countAvailable
#undef uloc_forLanguageTag
#undef uloc_getAvailable
#undef uloc_getBaseName
#undef uloc_getCharacterOrientation
#undef uloc_getCountry
#undef uloc_getDefault
#undef uloc_getDisplayCountry
#undef uloc_getDisplayKeyword
#undef uloc_getDisplayKeywordValue
#undef uloc_getDisplayLanguage
#undef uloc_getDisplayName
#undef uloc_getDisplayScript
#undef uloc_getDisplayVariant
#undef uloc_getISO3Country
#undef uloc_getISO3Language
#undef uloc_getISOCountries
#undef uloc_getISOLanguages
#undef uloc_getKeywordValue
#undef uloc_getLCID
#undef uloc_getLanguage
#undef uloc_getLineOrientation
#undef uloc_getLocaleForLCID
#undef uloc_getName
#undef uloc_getParent
#undef uloc_getScript
#undef uloc_getVariant
#undef uloc_isRightToLeft
#undef uloc_minimizeSubtags
#undef uloc_openAvailableByType
#undef uloc_openKeywords
#undef uloc_setDefault
#undef uloc_setKeywordValue
#undef uloc_toLanguageTag
#undef uloc_toLegacyKey
#undef uloc_toLegacyType
#undef uloc_toUnicodeLocaleKey
#undef uloc_toUnicodeLocaleType
#undef unorm2_append
#undef unorm2_close
#undef unorm2_composePair
#undef unorm2_getCombiningClass
#undef unorm2_getDecomposition
#undef unorm2_getInstance
#undef unorm2_getNFCInstance
#undef unorm2_getNFDInstance
#undef unorm2_getNFKCCasefoldInstance
#undef unorm2_getNFKCInstance
#undef unorm2_getNFKDInstance
#undef unorm2_getRawDecomposition
#undef unorm2_hasBoundaryAfter
#undef unorm2_hasBoundaryBefore
#undef unorm2_isInert
#undef unorm2_isNormalized
#undef unorm2_normalize
#undef unorm2_normalizeSecondAndAppend
#undef unorm2_openFiltered
#undef unorm2_quickCheck
#undef unorm2_spanQuickCheckYes
#undef unorm_compare
#undef unum_applyPattern
#undef unum_clone
#undef unum_close
#undef unum_countAvailable
#undef unum_format
#undef unum_formatDecimal
#undef unum_formatDouble
#undef unum_formatDoubleCurrency
#undef unum_formatDoubleForFields
#undef unum_formatInt64
#undef unum_getAttribute
#undef unum_getAvailable
#undef unum_getContext
#undef unum_getDoubleAttribute
#undef unum_getLocaleByType
#undef unum_getSymbol
#undef unum_getTextAttribute
#undef unum_open
#undef unum_parse
#undef unum_parseDecimal
#undef unum_parseDouble
#undef unum_parseDoubleCurrency
#undef unum_parseInt64
#undef unum_setAttribute
#undef unum_setContext
#undef unum_setDoubleAttribute
#undef unum_setSymbol
#undef unum_setTextAttribute
#undef unum_toPattern
#undef unumf_close
#undef unumf_formatDecimal
#undef unumf_formatDouble
#undef unumf_formatInt
#undef unumf_openForSkeletonAndLocale
#undef unumf_openForSkeletonAndLocaleWithError
#undef uscript_breaksBetweenLetters
#undef uscript_getCode
#undef uscript_getName
#undef uscript_getSampleString
#undef uscript_getScript
#undef uscript_getScriptExtensions
#undef uscript_getShortName
#undef uscript_getUsage
#undef uscript_hasScript
#undef uscript_isCased
#undef uscript_isRightToLeft
#undef uset_add
#undef uset_addString
#undef uset_clear
#undef uset_close
#undef uset_complement
#undef uset_contains
#undef uset_containsString
#undef uset_getItem
#undef uset_getItemCount
#undef uset_getRangeCount
#undef uset_isEmpty
#undef uset_open
#undef uset_openPattern
#undef uset_openPatternOptions
#undef uset_remove
#undef uset_removeString
#undef uset_size
#undef uset_toPattern
#undef utrans_clone
#undef utrans_close
#undef utrans_countAvailableIDs
#undef utrans_getSourceSet
#undef utrans_getUnicodeID
#undef utrans_openIDs
#undef utrans_openInverse
#undef utrans_openU
#undef utrans_register
#undef utrans_setFilter
#undef utrans_toRules
#undef utrans_transIncrementalUChars
#undef utrans_transUChars
#undef utrans_unregisterID

extern "C"
{
void UCNV_TO_U_CALLBACK_ESCAPE(const void *context, UConverterToUnicodeArgs *toUArgs, const char *codeUnits,
                               int32_t length, UConverterCallbackReason reason, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(UCNV_TO_U_CALLBACK_ESCAPE)(context, toUArgs, codeUnits, length, reason, err);
}
int32_t u_charDigitValue(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_charDigitValue)(c);
}
UCharDirection u_charDirection(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_charDirection)(c);
}
UChar32 u_charFromName(UCharNameChoice nameChoice, const char *name, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(u_charFromName)(nameChoice, name, pErrorCode);
}
UChar32 u_charMirror(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_charMirror)(c);
}
int32_t u_charName(UChar32 code, UCharNameChoice nameChoice, char *buffer, int32_t bufferLength,
                   UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(u_charName)(code, nameChoice, buffer, bufferLength, pErrorCode);
}
int8_t u_charType(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_charType)(c);
}
int32_t u_digit(UChar32 ch, int8_t radix)
{
    return U_ICU_ENTRY_POINT_RENAME(u_digit)(ch, radix);
}
void u_enumCharNames(UChar32 start, UChar32 limit, UEnumCharNamesFn *fn, void *context, UCharNameChoice nameChoice,
                     UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(u_enumCharNames)(start, limit, fn, context, nameChoice, pErrorCode);
}
void u_enumCharTypes(UCharEnumTypeRange *enumRange, const void *context)
{
    U_ICU_ENTRY_POINT_RENAME(u_enumCharTypes)(enumRange, context);
}
UChar32 u_foldCase(UChar32 c, uint32_t options)
{
    return U_ICU_ENTRY_POINT_RENAME(u_foldCase)(c, options);
}
UChar32 u_forDigit(int32_t digit, int8_t radix)
{
    return U_ICU_ENTRY_POINT_RENAME(u_forDigit)(digit, radix);
}
UChar32 u_getBidiPairedBracket(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getBidiPairedBracket)(c);
}
const USet *u_getBinaryPropertySet(UProperty property, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getBinaryPropertySet)(property, pErrorCode);
}
uint8_t u_getCombiningClass(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getCombiningClass)(c);
}
int32_t u_getFC_NFKC_Closure(UChar32 c, UChar *dest, int32_t destCapacity, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getFC_NFKC_Closure)(c, dest, destCapacity, pErrorCode);
}
int32_t u_getIntPropertyMaxValue(UProperty which)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getIntPropertyMaxValue)(which);
}
int32_t u_getIntPropertyMinValue(UProperty which)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getIntPropertyMinValue)(which);
}
int32_t u_getIntPropertyValue(UChar32 c, UProperty which)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getIntPropertyValue)(c, which);
}
double u_getNumericValue(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getNumericValue)(c);
}
UProperty u_getPropertyEnum(const char *alias)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getPropertyEnum)(alias);
}
const char *u_getPropertyName(UProperty property, UPropertyNameChoice nameChoice)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getPropertyName)(property, nameChoice);
}
int32_t u_getPropertyValueEnum(UProperty property, const char *alias)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getPropertyValueEnum)(property, alias);
}
const char *u_getPropertyValueName(UProperty property, int32_t value, UPropertyNameChoice nameChoice)
{
    return U_ICU_ENTRY_POINT_RENAME(u_getPropertyValueName)(property, value, nameChoice);
}
UBool u_hasBinaryProperty(UChar32 c, UProperty which)
{
    return U_ICU_ENTRY_POINT_RENAME(u_hasBinaryProperty)(c, which);
}
UBool u_isIDIgnorable(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isIDIgnorable)(c);
}
UBool u_isIDPart(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isIDPart)(c);
}
UBool u_isIDStart(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isIDStart)(c);
}
UBool u_isISOControl(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isISOControl)(c);
}
UBool u_isJavaIDPart(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isJavaIDPart)(c);
}
UBool u_isJavaIDStart(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isJavaIDStart)(c);
}
UBool u_isJavaSpaceChar(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isJavaSpaceChar)(c);
}
UBool u_isMirrored(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isMirrored)(c);
}
UBool u_isUAlphabetic(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isUAlphabetic)(c);
}
UBool u_isULowercase(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isULowercase)(c);
}
UBool u_isUUppercase(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isUUppercase)(c);
}
UBool u_isUWhiteSpace(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isUWhiteSpace)(c);
}
UBool u_isWhitespace(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isWhitespace)(c);
}
UBool u_isalnum(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isalnum)(c);
}
UBool u_isalpha(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isalpha)(c);
}
UBool u_isbase(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isbase)(c);
}
UBool u_isblank(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isblank)(c);
}
UBool u_iscntrl(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_iscntrl)(c);
}
UBool u_isdefined(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isdefined)(c);
}
UBool u_isdigit(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isdigit)(c);
}
UBool u_isgraph(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isgraph)(c);
}
UBool u_islower(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_islower)(c);
}
UBool u_isprint(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isprint)(c);
}
UBool u_ispunct(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_ispunct)(c);
}
UBool u_isspace(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isspace)(c);
}
UBool u_istitle(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_istitle)(c);
}
UBool u_isupper(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isupper)(c);
}
UBool u_isxdigit(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_isxdigit)(c);
}
UBool u_stringHasBinaryProperty(const UChar *s, int32_t length, UProperty which)
{
    return U_ICU_ENTRY_POINT_RENAME(u_stringHasBinaryProperty)(s, length, which);
}
UChar32 u_tolower(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_tolower)(c);
}
UChar32 u_totitle(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_totitle)(c);
}
UChar32 u_toupper(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(u_toupper)(c);
}
void ubidi_close(UBiDi *pBiDi)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_close)(pBiDi);
}
int32_t ubidi_countParagraphs(UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_countParagraphs)(pBiDi);
}
int32_t ubidi_countRuns(UBiDi *pBiDi, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_countRuns)(pBiDi, pErrorCode);
}
UBiDiDirection ubidi_getBaseDirection(const UChar *text, int32_t length)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getBaseDirection)(text, length);
}
void ubidi_getClassCallback(UBiDi *pBiDi, UBiDiClassCallback **fn, const void **context)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_getClassCallback)(pBiDi, fn, context);
}
UCharDirection ubidi_getCustomizedClass(UBiDi *pBiDi, UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getCustomizedClass)(pBiDi, c);
}
UBiDiDirection ubidi_getDirection(const UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getDirection)(pBiDi);
}
int32_t ubidi_getLength(const UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getLength)(pBiDi);
}
UBiDiLevel ubidi_getLevelAt(const UBiDi *pBiDi, int32_t charIndex)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getLevelAt)(pBiDi, charIndex);
}
const UBiDiLevel *ubidi_getLevels(UBiDi *pBiDi, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getLevels)(pBiDi, pErrorCode);
}
int32_t ubidi_getLogicalIndex(UBiDi *pBiDi, int32_t visualIndex, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getLogicalIndex)(pBiDi, visualIndex, pErrorCode);
}
void ubidi_getLogicalMap(UBiDi *pBiDi, int32_t *indexMap, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_getLogicalMap)(pBiDi, indexMap, pErrorCode);
}
void ubidi_getLogicalRun(const UBiDi *pBiDi, int32_t logicalPosition, int32_t *pLogicalLimit, UBiDiLevel *pLevel)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_getLogicalRun)(pBiDi, logicalPosition, pLogicalLimit, pLevel);
}
UBiDiLevel ubidi_getParaLevel(const UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getParaLevel)(pBiDi);
}
int32_t ubidi_getParagraph(const UBiDi *pBiDi, int32_t charIndex, int32_t *pParaStart, int32_t *pParaLimit,
                           UBiDiLevel *pParaLevel, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getParagraph)(pBiDi, charIndex, pParaStart, pParaLimit, pParaLevel,
                                                        pErrorCode);
}
void ubidi_getParagraphByIndex(const UBiDi *pBiDi, int32_t paraIndex, int32_t *pParaStart, int32_t *pParaLimit,
                               UBiDiLevel *pParaLevel, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_getParagraphByIndex)(pBiDi, paraIndex, pParaStart, pParaLimit, pParaLevel,
                                                        pErrorCode);
}
int32_t ubidi_getProcessedLength(const UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getProcessedLength)(pBiDi);
}
UBiDiReorderingMode ubidi_getReorderingMode(UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getReorderingMode)(pBiDi);
}
uint32_t ubidi_getReorderingOptions(UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getReorderingOptions)(pBiDi);
}
int32_t ubidi_getResultLength(const UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getResultLength)(pBiDi);
}
const UChar *ubidi_getText(const UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getText)(pBiDi);
}
int32_t ubidi_getVisualIndex(UBiDi *pBiDi, int32_t logicalIndex, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getVisualIndex)(pBiDi, logicalIndex, pErrorCode);
}
void ubidi_getVisualMap(UBiDi *pBiDi, int32_t *indexMap, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_getVisualMap)(pBiDi, indexMap, pErrorCode);
}
UBiDiDirection ubidi_getVisualRun(UBiDi *pBiDi, int32_t runIndex, int32_t *pLogicalStart, int32_t *pLength)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_getVisualRun)(pBiDi, runIndex, pLogicalStart, pLength);
}
void ubidi_invertMap(const int32_t *srcMap, int32_t *destMap, int32_t length)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_invertMap)(srcMap, destMap, length);
}
UBool ubidi_isInverse(UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_isInverse)(pBiDi);
}
UBool ubidi_isOrderParagraphsLTR(UBiDi *pBiDi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_isOrderParagraphsLTR)(pBiDi);
}
UBiDi *ubidi_open()
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_open)();
}
UBiDi *ubidi_openSized(int32_t maxLength, int32_t maxRunCount, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_openSized)(maxLength, maxRunCount, pErrorCode);
}
void ubidi_orderParagraphsLTR(UBiDi *pBiDi, UBool orderParagraphsLTR)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_orderParagraphsLTR)(pBiDi, orderParagraphsLTR);
}
void ubidi_reorderLogical(const UBiDiLevel *levels, int32_t length, int32_t *indexMap)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_reorderLogical)(levels, length, indexMap);
}
void ubidi_reorderVisual(const UBiDiLevel *levels, int32_t length, int32_t *indexMap)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_reorderVisual)(levels, length, indexMap);
}
void ubidi_setClassCallback(UBiDi *pBiDi, UBiDiClassCallback *newFn, const void *newContext, UBiDiClassCallback **oldFn,
                            const void **oldContext, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setClassCallback)(pBiDi, newFn, newContext, oldFn, oldContext, pErrorCode);
}
void ubidi_setContext(UBiDi *pBiDi, const UChar *prologue, int32_t proLength, const UChar *epilogue, int32_t epiLength,
                      UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setContext)(pBiDi, prologue, proLength, epilogue, epiLength, pErrorCode);
}
void ubidi_setInverse(UBiDi *pBiDi, UBool isInverse)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setInverse)(pBiDi, isInverse);
}
void ubidi_setLine(const UBiDi *pParaBiDi, int32_t start, int32_t limit, UBiDi *pLineBiDi, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setLine)(pParaBiDi, start, limit, pLineBiDi, pErrorCode);
}
void ubidi_setPara(UBiDi *pBiDi, const UChar *text, int32_t length, UBiDiLevel paraLevel, UBiDiLevel *embeddingLevels,
                   UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setPara)(pBiDi, text, length, paraLevel, embeddingLevels, pErrorCode);
}
void ubidi_setReorderingMode(UBiDi *pBiDi, UBiDiReorderingMode reorderingMode)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setReorderingMode)(pBiDi, reorderingMode);
}
void ubidi_setReorderingOptions(UBiDi *pBiDi, uint32_t reorderingOptions)
{
    U_ICU_ENTRY_POINT_RENAME(ubidi_setReorderingOptions)(pBiDi, reorderingOptions);
}
int32_t ubidi_writeReordered(UBiDi *pBiDi, UChar *dest, int32_t destSize, uint16_t options, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_writeReordered)(pBiDi, dest, destSize, options, pErrorCode);
}
int32_t ubidi_writeReverse(const UChar *src, int32_t srcLength, UChar *dest, int32_t destSize, uint16_t options,
                           UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ubidi_writeReverse)(src, srcLength, dest, destSize, options, pErrorCode);
}
UBlockCode ublock_getCode(UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(ublock_getCode)(c);
}
UBreakIterator *ubrk_clone(const UBreakIterator *bi, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_clone)(bi, status);
}
void ubrk_close(UBreakIterator *bi)
{
    U_ICU_ENTRY_POINT_RENAME(ubrk_close)(bi);
}
int32_t ubrk_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_countAvailable)();
}
int32_t ubrk_current(const UBreakIterator *bi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_current)(bi);
}
int32_t ubrk_first(UBreakIterator *bi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_first)(bi);
}
int32_t ubrk_following(UBreakIterator *bi, int32_t offset)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_following)(bi, offset);
}
const char *ubrk_getAvailable(int32_t index)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_getAvailable)(index);
}
int32_t ubrk_getBinaryRules(UBreakIterator *bi, uint8_t *binaryRules, int32_t rulesCapacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_getBinaryRules)(bi, binaryRules, rulesCapacity, status);
}
const char *ubrk_getLocaleByType(const UBreakIterator *bi, ULocDataLocaleType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_getLocaleByType)(bi, type, status);
}
int32_t ubrk_getRuleStatus(UBreakIterator *bi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_getRuleStatus)(bi);
}
int32_t ubrk_getRuleStatusVec(UBreakIterator *bi, int32_t *fillInVec, int32_t capacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_getRuleStatusVec)(bi, fillInVec, capacity, status);
}
UBool ubrk_isBoundary(UBreakIterator *bi, int32_t offset)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_isBoundary)(bi, offset);
}
int32_t ubrk_last(UBreakIterator *bi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_last)(bi);
}
int32_t ubrk_next(UBreakIterator *bi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_next)(bi);
}
UBreakIterator *ubrk_open(UBreakIteratorType type, const char *locale, const UChar *text, int32_t textLength,
                          UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_open)(type, locale, text, textLength, status);
}
UBreakIterator *ubrk_openBinaryRules(const uint8_t *binaryRules, int32_t rulesLength, const UChar *text,
                                     int32_t textLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_openBinaryRules)(binaryRules, rulesLength, text, textLength, status);
}
UBreakIterator *ubrk_openRules(const UChar *rules, int32_t rulesLength, const UChar *text, int32_t textLength,
                               UParseError *parseErr, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_openRules)(rules, rulesLength, text, textLength, parseErr, status);
}
int32_t ubrk_preceding(UBreakIterator *bi, int32_t offset)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_preceding)(bi, offset);
}
int32_t ubrk_previous(UBreakIterator *bi)
{
    return U_ICU_ENTRY_POINT_RENAME(ubrk_previous)(bi);
}
void ubrk_setText(UBreakIterator *bi, const UChar *text, int32_t textLength, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ubrk_setText)(bi, text, textLength, status);
}
void ucal_add(UCalendar *cal, UCalendarDateFields field, int32_t amount, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_add)(cal, field, amount, status);
}
void ucal_clear(UCalendar *calendar)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_clear)(calendar);
}
void ucal_clearField(UCalendar *cal, UCalendarDateFields field)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_clearField)(cal, field);
}
UCalendar *ucal_clone(const UCalendar *cal, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_clone)(cal, status);
}
void ucal_close(UCalendar *cal)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_close)(cal);
}
int32_t ucal_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_countAvailable)();
}
UBool ucal_equivalentTo(const UCalendar *cal1, const UCalendar *cal2)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_equivalentTo)(cal1, cal2);
}
int32_t ucal_get(const UCalendar *cal, UCalendarDateFields field, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_get)(cal, field, status);
}
int32_t ucal_getAttribute(const UCalendar *cal, UCalendarAttribute attr)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getAttribute)(cal, attr);
}
const char *ucal_getAvailable(int32_t localeIndex)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getAvailable)(localeIndex);
}
int32_t ucal_getCanonicalTimeZoneID(const UChar *id, int32_t len, UChar *result, int32_t resultCapacity,
                                    UBool *isSystemID, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getCanonicalTimeZoneID)(id, len, result, resultCapacity, isSystemID, status);
}
int32_t ucal_getDSTSavings(const UChar *zoneID, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getDSTSavings)(zoneID, ec);
}
UCalendarWeekdayType ucal_getDayOfWeekType(const UCalendar *cal, UCalendarDaysOfWeek dayOfWeek, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getDayOfWeekType)(cal, dayOfWeek, status);
}
int32_t ucal_getDefaultTimeZone(UChar *result, int32_t resultCapacity, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getDefaultTimeZone)(result, resultCapacity, ec);
}
int32_t ucal_getFieldDifference(UCalendar *cal, UDate target, UCalendarDateFields field, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getFieldDifference)(cal, target, field, status);
}
UDate ucal_getGregorianChange(const UCalendar *cal, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getGregorianChange)(cal, pErrorCode);
}
int32_t ucal_getHostTimeZone(UChar *result, int32_t resultCapacity, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getHostTimeZone)(result, resultCapacity, ec);
}
UEnumeration *ucal_getKeywordValuesForLocale(const char *key, const char *locale, UBool commonlyUsed,
                                             UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getKeywordValuesForLocale)(key, locale, commonlyUsed, status);
}
int32_t ucal_getLimit(const UCalendar *cal, UCalendarDateFields field, UCalendarLimitType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getLimit)(cal, field, type, status);
}
const char *ucal_getLocaleByType(const UCalendar *cal, ULocDataLocaleType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getLocaleByType)(cal, type, status);
}
UDate ucal_getMillis(const UCalendar *cal, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getMillis)(cal, status);
}
UDate ucal_getNow()
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getNow)();
}
const char *ucal_getTZDataVersion(UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getTZDataVersion)(status);
}
int32_t ucal_getTimeZoneDisplayName(const UCalendar *cal, UCalendarDisplayNameType type, const char *locale,
                                    UChar *result, int32_t resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getTimeZoneDisplayName)(cal, type, locale, result, resultLength, status);
}
int32_t ucal_getTimeZoneID(const UCalendar *cal, UChar *result, int32_t resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getTimeZoneID)(cal, result, resultLength, status);
}
int32_t ucal_getTimeZoneIDForWindowsID(const UChar *winid, int32_t len, const char *region, UChar *id,
                                       int32_t idCapacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getTimeZoneIDForWindowsID)(winid, len, region, id, idCapacity, status);
}
void ucal_getTimeZoneOffsetFromLocal(const UCalendar *cal, UTimeZoneLocalOption nonExistingTimeOpt,
                                     UTimeZoneLocalOption duplicatedTimeOpt, int32_t *rawOffset, int32_t *dstOffset,
                                     UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_getTimeZoneOffsetFromLocal)(cal, nonExistingTimeOpt, duplicatedTimeOpt, rawOffset,
                                                              dstOffset, status);
}
UBool ucal_getTimeZoneTransitionDate(const UCalendar *cal, UTimeZoneTransitionType type, UDate *transition,
                                     UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getTimeZoneTransitionDate)(cal, type, transition, status);
}
const char *ucal_getType(const UCalendar *cal, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getType)(cal, status);
}
int32_t ucal_getWeekendTransition(const UCalendar *cal, UCalendarDaysOfWeek dayOfWeek, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getWeekendTransition)(cal, dayOfWeek, status);
}
int32_t ucal_getWindowsTimeZoneID(const UChar *id, int32_t len, UChar *winid, int32_t winidCapacity,
                                  UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_getWindowsTimeZoneID)(id, len, winid, winidCapacity, status);
}
UBool ucal_inDaylightTime(const UCalendar *cal, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_inDaylightTime)(cal, status);
}
UBool ucal_isSet(const UCalendar *cal, UCalendarDateFields field)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_isSet)(cal, field);
}
UBool ucal_isWeekend(const UCalendar *cal, UDate date, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_isWeekend)(cal, date, status);
}
UCalendar *ucal_open(const UChar *zoneID, int32_t len, const char *locale, UCalendarType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_open)(zoneID, len, locale, type, status);
}
UEnumeration *ucal_openCountryTimeZones(const char *country, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_openCountryTimeZones)(country, ec);
}
UEnumeration *ucal_openTimeZoneIDEnumeration(USystemTimeZoneType zoneType, const char *region, const int32_t *rawOffset,
                                             UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_openTimeZoneIDEnumeration)(zoneType, region, rawOffset, ec);
}
UEnumeration *ucal_openTimeZones(UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(ucal_openTimeZones)(ec);
}
void ucal_roll(UCalendar *cal, UCalendarDateFields field, int32_t amount, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_roll)(cal, field, amount, status);
}
void ucal_set(UCalendar *cal, UCalendarDateFields field, int32_t value)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_set)(cal, field, value);
}
void ucal_setAttribute(UCalendar *cal, UCalendarAttribute attr, int32_t newValue)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setAttribute)(cal, attr, newValue);
}
void ucal_setDate(UCalendar *cal, int32_t year, int32_t month, int32_t date, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setDate)(cal, year, month, date, status);
}
void ucal_setDateTime(UCalendar *cal, int32_t year, int32_t month, int32_t date, int32_t hour, int32_t minute,
                      int32_t second, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setDateTime)(cal, year, month, date, hour, minute, second, status);
}
void ucal_setDefaultTimeZone(const UChar *zoneID, UErrorCode *ec)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setDefaultTimeZone)(zoneID, ec);
}
void ucal_setGregorianChange(UCalendar *cal, UDate date, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setGregorianChange)(cal, date, pErrorCode);
}
void ucal_setMillis(UCalendar *cal, UDate dateTime, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setMillis)(cal, dateTime, status);
}
void ucal_setTimeZone(UCalendar *cal, const UChar *zoneID, int32_t len, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucal_setTimeZone)(cal, zoneID, len, status);
}
UConverter *ucnv_clone(const UConverter *cnv, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_clone)(cnv, status);
}
void ucnv_close(UConverter *converter)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_close)(converter);
}
int ucnv_compareNames(const char *name1, const char *name2)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_compareNames)(name1, name2);
}
int32_t ucnv_convert(const char *toConverterName, const char *fromConverterName, char *target, int32_t targetCapacity,
                     const char *source, int32_t sourceLength, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_convert)(toConverterName, fromConverterName, target, targetCapacity, source,
                                                  sourceLength, pErrorCode);
}
void ucnv_convertEx(UConverter *targetCnv, UConverter *sourceCnv, char **target, const char *targetLimit,
                    const char **source, const char *sourceLimit, UChar *pivotStart, UChar **pivotSource,
                    UChar **pivotTarget, const UChar *pivotLimit, UBool reset, UBool flush, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_convertEx)(targetCnv, sourceCnv, target, targetLimit, source, sourceLimit, pivotStart,
                                             pivotSource, pivotTarget, pivotLimit, reset, flush, pErrorCode);
}
uint16_t ucnv_countAliases(const char *alias, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_countAliases)(alias, pErrorCode);
}
int32_t ucnv_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_countAvailable)();
}
uint16_t ucnv_countStandards()
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_countStandards)();
}
const char *ucnv_detectUnicodeSignature(const char *source, int32_t sourceLength, int32_t *signatureLength,
                                        UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_detectUnicodeSignature)(source, sourceLength, signatureLength, pErrorCode);
}
void ucnv_fixFileSeparator(const UConverter *cnv, UChar *source, int32_t sourceLen)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_fixFileSeparator)(cnv, source, sourceLen);
}
int32_t ucnv_flushCache()
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_flushCache)();
}
int32_t ucnv_fromAlgorithmic(UConverter *cnv, UConverterType algorithmicType, char *target, int32_t targetCapacity,
                             const char *source, int32_t sourceLength, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_fromAlgorithmic)(cnv, algorithmicType, target, targetCapacity, source,
                                                          sourceLength, pErrorCode);
}
int32_t ucnv_fromUChars(UConverter *cnv, char *dest, int32_t destCapacity, const UChar *src, int32_t srcLength,
                        UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_fromUChars)(cnv, dest, destCapacity, src, srcLength, pErrorCode);
}
int32_t ucnv_fromUCountPending(const UConverter *cnv, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_fromUCountPending)(cnv, status);
}
void ucnv_fromUnicode(UConverter *converter, char **target, const char *targetLimit, const UChar **source,
                      const UChar *sourceLimit, int32_t *offsets, UBool flush, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_fromUnicode)(converter, target, targetLimit, source, sourceLimit, offsets, flush,
                                               err);
}
const char *ucnv_getAlias(const char *alias, uint16_t n, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getAlias)(alias, n, pErrorCode);
}
void ucnv_getAliases(const char *alias, const char **aliases, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getAliases)(alias, aliases, pErrorCode);
}
const char *ucnv_getAvailableName(int32_t n)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getAvailableName)(n);
}
int32_t ucnv_getCCSID(const UConverter *converter, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getCCSID)(converter, err);
}
const char *ucnv_getCanonicalName(const char *alias, const char *standard, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getCanonicalName)(alias, standard, pErrorCode);
}
const char *ucnv_getDefaultName()
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getDefaultName)();
}
int32_t ucnv_getDisplayName(const UConverter *converter, const char *displayLocale, UChar *displayName,
                            int32_t displayNameCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getDisplayName)(converter, displayLocale, displayName, displayNameCapacity,
                                                         err);
}
void ucnv_getFromUCallBack(const UConverter *converter, UConverterFromUCallback *action, const void **context)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getFromUCallBack)(converter, action, context);
}
void ucnv_getInvalidChars(const UConverter *converter, char *errBytes, int8_t *len, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getInvalidChars)(converter, errBytes, len, err);
}
void ucnv_getInvalidUChars(const UConverter *converter, UChar *errUChars, int8_t *len, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getInvalidUChars)(converter, errUChars, len, err);
}
int8_t ucnv_getMaxCharSize(const UConverter *converter)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getMaxCharSize)(converter);
}
int8_t ucnv_getMinCharSize(const UConverter *converter)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getMinCharSize)(converter);
}
const char *ucnv_getName(const UConverter *converter, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getName)(converter, err);
}
UChar32 ucnv_getNextUChar(UConverter *converter, const char **source, const char *sourceLimit, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getNextUChar)(converter, source, sourceLimit, err);
}
UConverterPlatform ucnv_getPlatform(const UConverter *converter, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getPlatform)(converter, err);
}
const char *ucnv_getStandard(uint16_t n, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getStandard)(n, pErrorCode);
}
const char *ucnv_getStandardName(const char *name, const char *standard, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getStandardName)(name, standard, pErrorCode);
}
void ucnv_getStarters(const UConverter *converter, UBool starters[256], UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getStarters)(converter, starters, err);
}
void ucnv_getSubstChars(const UConverter *converter, char *subChars, int8_t *len, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getSubstChars)(converter, subChars, len, err);
}
void ucnv_getToUCallBack(const UConverter *converter, UConverterToUCallback *action, const void **context)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_getToUCallBack)(converter, action, context);
}
UConverterType ucnv_getType(const UConverter *converter)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_getType)(converter);
}
UBool ucnv_isAmbiguous(const UConverter *cnv)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_isAmbiguous)(cnv);
}
UBool ucnv_isFixedWidth(UConverter *cnv, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_isFixedWidth)(cnv, status);
}
UConverter *ucnv_open(const char *converterName, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_open)(converterName, err);
}
UEnumeration *ucnv_openAllNames(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_openAllNames)(pErrorCode);
}
UConverter *ucnv_openCCSID(int32_t codepage, UConverterPlatform platform, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_openCCSID)(codepage, platform, err);
}
UConverter *ucnv_openPackage(const char *packageName, const char *converterName, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_openPackage)(packageName, converterName, err);
}
UEnumeration *ucnv_openStandardNames(const char *convName, const char *standard, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_openStandardNames)(convName, standard, pErrorCode);
}
UConverter *ucnv_openU(const UChar *name, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_openU)(name, err);
}
void ucnv_reset(UConverter *converter)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_reset)(converter);
}
void ucnv_resetFromUnicode(UConverter *converter)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_resetFromUnicode)(converter);
}
void ucnv_resetToUnicode(UConverter *converter)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_resetToUnicode)(converter);
}
void ucnv_setDefaultName(const char *name)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_setDefaultName)(name);
}
void ucnv_setFallback(UConverter *cnv, UBool usesFallback)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_setFallback)(cnv, usesFallback);
}
void ucnv_setFromUCallBack(UConverter *converter, UConverterFromUCallback newAction, const void *newContext,
                           UConverterFromUCallback *oldAction, const void **oldContext, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_setFromUCallBack)(converter, newAction, newContext, oldAction, oldContext, err);
}
void ucnv_setSubstChars(UConverter *converter, const char *subChars, int8_t len, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_setSubstChars)(converter, subChars, len, err);
}
void ucnv_setSubstString(UConverter *cnv, const UChar *s, int32_t length, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_setSubstString)(cnv, s, length, err);
}
void ucnv_setToUCallBack(UConverter *converter, UConverterToUCallback newAction, const void *newContext,
                         UConverterToUCallback *oldAction, const void **oldContext, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_setToUCallBack)(converter, newAction, newContext, oldAction, oldContext, err);
}
int32_t ucnv_toAlgorithmic(UConverterType algorithmicType, UConverter *cnv, char *target, int32_t targetCapacity,
                           const char *source, int32_t sourceLength, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_toAlgorithmic)(algorithmicType, cnv, target, targetCapacity, source,
                                                        sourceLength, pErrorCode);
}
int32_t ucnv_toUChars(UConverter *cnv, UChar *dest, int32_t destCapacity, const char *src, int32_t srcLength,
                      UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_toUChars)(cnv, dest, destCapacity, src, srcLength, pErrorCode);
}
int32_t ucnv_toUCountPending(const UConverter *cnv, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_toUCountPending)(cnv, status);
}
void ucnv_toUnicode(UConverter *converter, UChar **target, const UChar *targetLimit, const char **source,
                    const char *sourceLimit, int32_t *offsets, UBool flush, UErrorCode *err)
{
    U_ICU_ENTRY_POINT_RENAME(ucnv_toUnicode)(converter, target, targetLimit, source, sourceLimit, offsets, flush, err);
}
UBool ucnv_usesFallback(const UConverter *cnv)
{
    return U_ICU_ENTRY_POINT_RENAME(ucnv_usesFallback)(cnv);
}
UCollator *ucol_clone(const UCollator *coll, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_clone)(coll, status);
}
int32_t ucol_cloneBinary(const UCollator *coll, uint8_t *buffer, int32_t capacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_cloneBinary)(coll, buffer, capacity, status);
}
void ucol_close(UCollator *coll)
{
    U_ICU_ENTRY_POINT_RENAME(ucol_close)(coll);
}
int32_t ucol_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_countAvailable)();
}
UBool ucol_equal(const UCollator *coll, const UChar *source, int32_t sourceLength, const UChar *target,
                 int32_t targetLength)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_equal)(coll, source, sourceLength, target, targetLength);
}
UColAttributeValue ucol_getAttribute(const UCollator *coll, UColAttribute attr, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getAttribute)(coll, attr, status);
}
const char *ucol_getAvailable(int32_t localeIndex)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getAvailable)(localeIndex);
}
int32_t ucol_getBound(const uint8_t *source, int32_t sourceLength, UColBoundMode boundType, uint32_t noOfLevels,
                      uint8_t *result, int32_t resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getBound)(source, sourceLength, boundType, noOfLevels, result, resultLength,
                                                   status);
}
void ucol_getContractionsAndExpansions(const UCollator *coll, USet *contractions, USet *expansions, UBool addPrefixes,
                                       UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucol_getContractionsAndExpansions)(coll, contractions, expansions, addPrefixes, status);
}
int32_t ucol_getDisplayName(const char *objLoc, const char *dispLoc, UChar *result, int32_t resultLength,
                            UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getDisplayName)(objLoc, dispLoc, result, resultLength, status);
}
int32_t ucol_getEquivalentReorderCodes(int32_t reorderCode, int32_t *dest, int32_t destCapacity,
                                       UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getEquivalentReorderCodes)(reorderCode, dest, destCapacity, pErrorCode);
}
int32_t ucol_getFunctionalEquivalent(char *result, int32_t resultCapacity, const char *keyword, const char *locale,
                                     UBool *isAvailable, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getFunctionalEquivalent)(result, resultCapacity, keyword, locale, isAvailable,
                                                                  status);
}
UEnumeration *ucol_getKeywordValues(const char *keyword, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getKeywordValues)(keyword, status);
}
UEnumeration *ucol_getKeywordValuesForLocale(const char *key, const char *locale, UBool commonlyUsed,
                                             UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getKeywordValuesForLocale)(key, locale, commonlyUsed, status);
}
UEnumeration *ucol_getKeywords(UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getKeywords)(status);
}
const char *ucol_getLocaleByType(const UCollator *coll, ULocDataLocaleType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getLocaleByType)(coll, type, status);
}
UColReorderCode ucol_getMaxVariable(const UCollator *coll)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getMaxVariable)(coll);
}
int32_t ucol_getReorderCodes(const UCollator *coll, int32_t *dest, int32_t destCapacity, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getReorderCodes)(coll, dest, destCapacity, pErrorCode);
}
const UChar *ucol_getRules(const UCollator *coll, int32_t *length)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getRules)(coll, length);
}
int32_t ucol_getRulesEx(const UCollator *coll, UColRuleOption delta, UChar *buffer, int32_t bufferLen)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getRulesEx)(coll, delta, buffer, bufferLen);
}
int32_t ucol_getSortKey(const UCollator *coll, const UChar *source, int32_t sourceLength, uint8_t *result,
                        int32_t resultLength)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getSortKey)(coll, source, sourceLength, result, resultLength);
}
UCollationStrength ucol_getStrength(const UCollator *coll)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getStrength)(coll);
}
USet *ucol_getTailoredSet(const UCollator *coll, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getTailoredSet)(coll, status);
}
uint32_t ucol_getVariableTop(const UCollator *coll, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_getVariableTop)(coll, status);
}
UBool ucol_greater(const UCollator *coll, const UChar *source, int32_t sourceLength, const UChar *target,
                   int32_t targetLength)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_greater)(coll, source, sourceLength, target, targetLength);
}
UBool ucol_greaterOrEqual(const UCollator *coll, const UChar *source, int32_t sourceLength, const UChar *target,
                          int32_t targetLength)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_greaterOrEqual)(coll, source, sourceLength, target, targetLength);
}
int32_t ucol_mergeSortkeys(const uint8_t *src1, int32_t src1Length, const uint8_t *src2, int32_t src2Length,
                           uint8_t *dest, int32_t destCapacity)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_mergeSortkeys)(src1, src1Length, src2, src2Length, dest, destCapacity);
}
UCollator *ucol_open(const char *loc, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_open)(loc, status);
}
UEnumeration *ucol_openAvailableLocales(UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_openAvailableLocales)(status);
}
UCollator *ucol_openBinary(const uint8_t *bin, int32_t length, const UCollator *base, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_openBinary)(bin, length, base, status);
}
UCollator *ucol_openRules(const UChar *rules, int32_t rulesLength, UColAttributeValue normalizationMode,
                          UCollationStrength strength, UParseError *parseError, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_openRules)(rules, rulesLength, normalizationMode, strength, parseError,
                                                    status);
}
void ucol_setAttribute(UCollator *coll, UColAttribute attr, UColAttributeValue value, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(ucol_setAttribute)(coll, attr, value, status);
}
void ucol_setMaxVariable(UCollator *coll, UColReorderCode group, UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ucol_setMaxVariable)(coll, group, pErrorCode);
}
void ucol_setReorderCodes(UCollator *coll, const int32_t *reorderCodes, int32_t reorderCodesLength,
                          UErrorCode *pErrorCode)
{
    U_ICU_ENTRY_POINT_RENAME(ucol_setReorderCodes)(coll, reorderCodes, reorderCodesLength, pErrorCode);
}
void ucol_setStrength(UCollator *coll, UCollationStrength strength)
{
    U_ICU_ENTRY_POINT_RENAME(ucol_setStrength)(coll, strength);
}
UCollationResult ucol_strcoll(const UCollator *coll, const UChar *source, int32_t sourceLength, const UChar *target,
                              int32_t targetLength)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_strcoll)(coll, source, sourceLength, target, targetLength);
}
UCollationResult ucol_strcollUTF8(const UCollator *coll, const char *source, int32_t sourceLength, const char *target,
                                  int32_t targetLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ucol_strcollUTF8)(coll, source, sourceLength, target, targetLength, status);
}
void udat_adoptNumberFormat(UDateFormat *fmt, UNumberFormat *numberFormatToAdopt)
{
    U_ICU_ENTRY_POINT_RENAME(udat_adoptNumberFormat)(fmt, numberFormatToAdopt);
}
void udat_adoptNumberFormatForFields(UDateFormat *fmt, const UChar *fields, UNumberFormat *numberFormatToSet,
                                     UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(udat_adoptNumberFormatForFields)(fmt, fields, numberFormatToSet, status);
}
void udat_applyPattern(UDateFormat *format, UBool localized, const UChar *pattern, int32_t patternLength)
{
    U_ICU_ENTRY_POINT_RENAME(udat_applyPattern)(format, localized, pattern, patternLength);
}
UDateFormat *udat_clone(const UDateFormat *fmt, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_clone)(fmt, status);
}
void udat_close(UDateFormat *format)
{
    U_ICU_ENTRY_POINT_RENAME(udat_close)(format);
}
int32_t udat_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(udat_countAvailable)();
}
int32_t udat_countSymbols(const UDateFormat *fmt, UDateFormatSymbolType type)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_countSymbols)(fmt, type);
}
int32_t udat_format(const UDateFormat *format, UDate dateToFormat, UChar *result, int32_t resultLength,
                    UFieldPosition *position, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_format)(format, dateToFormat, result, resultLength, position, status);
}
int32_t udat_formatCalendar(const UDateFormat *format, UCalendar *calendar, UChar *result, int32_t capacity,
                            UFieldPosition *position, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_formatCalendar)(format, calendar, result, capacity, position, status);
}
int32_t udat_formatCalendarForFields(const UDateFormat *format, UCalendar *calendar, UChar *result, int32_t capacity,
                                     UFieldPositionIterator *fpositer, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_formatCalendarForFields)(format, calendar, result, capacity, fpositer, status);
}
int32_t udat_formatForFields(const UDateFormat *format, UDate dateToFormat, UChar *result, int32_t resultLength,
                             UFieldPositionIterator *fpositer, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_formatForFields)(format, dateToFormat, result, resultLength, fpositer, status);
}
UDate udat_get2DigitYearStart(const UDateFormat *fmt, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_get2DigitYearStart)(fmt, status);
}
const char *udat_getAvailable(int32_t localeIndex)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getAvailable)(localeIndex);
}
UBool udat_getBooleanAttribute(const UDateFormat *fmt, UDateFormatBooleanAttribute attr, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getBooleanAttribute)(fmt, attr, status);
}
const UCalendar *udat_getCalendar(const UDateFormat *fmt)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getCalendar)(fmt);
}
UDisplayContext udat_getContext(const UDateFormat *fmt, UDisplayContextType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getContext)(fmt, type, status);
}
const char *udat_getLocaleByType(const UDateFormat *fmt, ULocDataLocaleType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getLocaleByType)(fmt, type, status);
}
const UNumberFormat *udat_getNumberFormat(const UDateFormat *fmt)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getNumberFormat)(fmt);
}
const UNumberFormat *udat_getNumberFormatForField(const UDateFormat *fmt, UChar field)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getNumberFormatForField)(fmt, field);
}
int32_t udat_getSymbols(const UDateFormat *fmt, UDateFormatSymbolType type, int32_t symbolIndex, UChar *result,
                        int32_t resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_getSymbols)(fmt, type, symbolIndex, result, resultLength, status);
}
UBool udat_isLenient(const UDateFormat *fmt)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_isLenient)(fmt);
}
UDateFormat *udat_open(UDateFormatStyle timeStyle, UDateFormatStyle dateStyle, const char *locale, const UChar *tzID,
                       int32_t tzIDLength, const UChar *pattern, int32_t patternLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_open)(timeStyle, dateStyle, locale, tzID, tzIDLength, pattern, patternLength,
                                               status);
}
UDate udat_parse(const UDateFormat *format, const UChar *text, int32_t textLength, int32_t *parsePos,
                 UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_parse)(format, text, textLength, parsePos, status);
}
void udat_parseCalendar(const UDateFormat *format, UCalendar *calendar, const UChar *text, int32_t textLength,
                        int32_t *parsePos, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(udat_parseCalendar)(format, calendar, text, textLength, parsePos, status);
}
void udat_set2DigitYearStart(UDateFormat *fmt, UDate d, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(udat_set2DigitYearStart)(fmt, d, status);
}
void udat_setBooleanAttribute(UDateFormat *fmt, UDateFormatBooleanAttribute attr, UBool newValue, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(udat_setBooleanAttribute)(fmt, attr, newValue, status);
}
void udat_setCalendar(UDateFormat *fmt, const UCalendar *calendarToSet)
{
    U_ICU_ENTRY_POINT_RENAME(udat_setCalendar)(fmt, calendarToSet);
}
void udat_setContext(UDateFormat *fmt, UDisplayContext value, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(udat_setContext)(fmt, value, status);
}
void udat_setLenient(UDateFormat *fmt, UBool isLenient)
{
    U_ICU_ENTRY_POINT_RENAME(udat_setLenient)(fmt, isLenient);
}
void udat_setNumberFormat(UDateFormat *fmt, const UNumberFormat *numberFormatToSet)
{
    U_ICU_ENTRY_POINT_RENAME(udat_setNumberFormat)(fmt, numberFormatToSet);
}
void udat_setSymbols(UDateFormat *format, UDateFormatSymbolType type, int32_t symbolIndex, UChar *value,
                     int32_t valueLength, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(udat_setSymbols)(format, type, symbolIndex, value, valueLength, status);
}
UCalendarDateFields udat_toCalendarDateField(UDateFormatField field)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_toCalendarDateField)(field);
}
int32_t udat_toPattern(const UDateFormat *fmt, UBool localized, UChar *result, int32_t resultLength,
                       UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(udat_toPattern)(fmt, localized, result, resultLength, status);
}
void uenum_close(UEnumeration *en)
{
    U_ICU_ENTRY_POINT_RENAME(uenum_close)(en);
}
int32_t uenum_count(UEnumeration *en, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uenum_count)(en, status);
}
const char *uenum_next(UEnumeration *en, int32_t *resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uenum_next)(en, resultLength, status);
}
void uenum_reset(UEnumeration *en, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(uenum_reset)(en, status);
}
const UChar *uenum_unext(UEnumeration *en, int32_t *resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uenum_unext)(en, resultLength, status);
}
void ufieldpositer_close(UFieldPositionIterator *fpositer)
{
    U_ICU_ENTRY_POINT_RENAME(ufieldpositer_close)(fpositer);
}
int32_t ufieldpositer_next(UFieldPositionIterator *fpositer, int32_t *beginIndex, int32_t *endIndex)
{
    return U_ICU_ENTRY_POINT_RENAME(ufieldpositer_next)(fpositer, beginIndex, endIndex);
}
UFieldPositionIterator *ufieldpositer_open(UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(ufieldpositer_open)(status);
}
void uidna_close(UIDNA *idna)
{
    U_ICU_ENTRY_POINT_RENAME(uidna_close)(idna);
}
int32_t uidna_labelToASCII(const UIDNA *idna, const UChar *label, int32_t length, UChar *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_labelToASCII)(idna, label, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_labelToASCII_UTF8(const UIDNA *idna, const char *label, int32_t length, char *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_labelToASCII_UTF8)(idna, label, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_labelToUnicode(const UIDNA *idna, const UChar *label, int32_t length, UChar *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_labelToUnicode)(idna, label, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_labelToUnicodeUTF8(const UIDNA *idna, const char *label, int32_t length, char *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_labelToUnicodeUTF8)(idna, label, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_nameToASCII(const UIDNA *idna, const UChar *name, int32_t length, UChar *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_nameToASCII)(idna, name, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_nameToASCII_UTF8(const UIDNA *idna, const char *name, int32_t length, char *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_nameToASCII_UTF8)(idna, name, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_nameToUnicode(const UIDNA *idna, const UChar *name, int32_t length, UChar *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_nameToUnicode)(idna, name, length, dest, capacity, pInfo, pErrorCode);
}
int32_t uidna_nameToUnicodeUTF8(const UIDNA *idna, const char *name, int32_t length, char *dest, int32_t capacity,
    UIDNAInfo *pInfo, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_nameToUnicodeUTF8)(idna, name, length, dest, capacity, pInfo, pErrorCode);
}
UIDNA* uidna_openUTS46(uint32_t options, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uidna_openUTS46)(options, pErrorCode);
}
int32_t uloc_acceptLanguage(char *result, int32_t resultAvailable, UAcceptResult *outResult, const char **acceptList,
                            int32_t acceptListCount, UEnumeration *availableLocales, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_acceptLanguage)(result, resultAvailable, outResult, acceptList,
                                                         acceptListCount, availableLocales, status);
}
int32_t uloc_acceptLanguageFromHTTP(char *result, int32_t resultAvailable, UAcceptResult *outResult,
                                    const char *httpAcceptLanguage, UEnumeration *availableLocales,
                                    UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_acceptLanguageFromHTTP)(result, resultAvailable, outResult, httpAcceptLanguage,
                                                                 availableLocales, status);
}
int32_t uloc_addLikelySubtags(const char *localeID, char *maximizedLocaleID, int32_t maximizedLocaleIDCapacity,
                              UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_addLikelySubtags)(localeID, maximizedLocaleID, maximizedLocaleIDCapacity, err);
}
int32_t uloc_canonicalize(const char *localeID, char *name, int32_t nameCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_canonicalize)(localeID, name, nameCapacity, err);
}
int32_t uloc_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_countAvailable)();
}
int32_t uloc_forLanguageTag(const char *langtag, char *localeID, int32_t localeIDCapacity, int32_t *parsedLength,
                            UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_forLanguageTag)(langtag, localeID, localeIDCapacity, parsedLength, err);
}
const char *uloc_getAvailable(int32_t n)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getAvailable)(n);
}
int32_t uloc_getBaseName(const char *localeID, char *name, int32_t nameCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getBaseName)(localeID, name, nameCapacity, err);
}
ULayoutType uloc_getCharacterOrientation(const char *localeId, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getCharacterOrientation)(localeId, status);
}
int32_t uloc_getCountry(const char *localeID, char *country, int32_t countryCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getCountry)(localeID, country, countryCapacity, err);
}
const char *uloc_getDefault()
{
#ifdef ICU_SUPPORT_LIBBEGETUTIL
    if (g_isCustomLocale) {
        return U_ICU_ENTRY_POINT_RENAME(uloc_getDefault)();
    }

    static char param[128];
    const char *LOCALE_KEY = "persist.global.locale";
    const char *DEFAULT_LOCALE_KEY = "const.global.locale";
    int status = GetParameter(LOCALE_KEY, "", param, 128);
    if (status <= 0) {
        status = GetParameter(DEFAULT_LOCALE_KEY, "", param, 128);
    }
    if (status <= 0) {
        return "";
    }
    return param;
#else
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDefault)();
#endif
}
int32_t uloc_getDisplayCountry(const char *locale, const char *displayLocale, UChar *country, int32_t countryCapacity,
                               UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayCountry)(locale, displayLocale, country, countryCapacity, status);
}
int32_t uloc_getDisplayKeyword(const char *keyword, const char *displayLocale, UChar *dest, int32_t destCapacity,
                               UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayKeyword)(keyword, displayLocale, dest, destCapacity, status);
}
int32_t uloc_getDisplayKeywordValue(const char *locale, const char *keyword, const char *displayLocale, UChar *dest,
                                    int32_t destCapacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayKeywordValue)(locale, keyword, displayLocale, dest, destCapacity,
                                                                 status);
}
int32_t uloc_getDisplayLanguage(const char *locale, const char *displayLocale, UChar *language,
                                int32_t languageCapacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayLanguage)(locale, displayLocale, language, languageCapacity, status);
}
int32_t uloc_getDisplayName(const char *localeID, const char *inLocaleID, UChar *result, int32_t maxResultSize,
                            UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayName)(localeID, inLocaleID, result, maxResultSize, err);
}
int32_t uloc_getDisplayScript(const char *locale, const char *displayLocale, UChar *script, int32_t scriptCapacity,
                              UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayScript)(locale, displayLocale, script, scriptCapacity, status);
}
int32_t uloc_getDisplayVariant(const char *locale, const char *displayLocale, UChar *variant, int32_t variantCapacity,
                               UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getDisplayVariant)(locale, displayLocale, variant, variantCapacity, status);
}
const char *uloc_getISO3Country(const char *localeID)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getISO3Country)(localeID);
}
const char *uloc_getISO3Language(const char *localeID)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getISO3Language)(localeID);
}
const char *const *uloc_getISOCountries()
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getISOCountries)();
}
const char *const *uloc_getISOLanguages()
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getISOLanguages)();
}
int32_t uloc_getKeywordValue(const char *localeID, const char *keywordName, char *buffer, int32_t bufferCapacity,
                             UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getKeywordValue)(localeID, keywordName, buffer, bufferCapacity, status);
}
uint32_t uloc_getLCID(const char *localeID)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getLCID)(localeID);
}
int32_t uloc_getLanguage(const char *localeID, char *language, int32_t languageCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getLanguage)(localeID, language, languageCapacity, err);
}
ULayoutType uloc_getLineOrientation(const char *localeId, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getLineOrientation)(localeId, status);
}
int32_t uloc_getLocaleForLCID(uint32_t hostID, char *locale, int32_t localeCapacity, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getLocaleForLCID)(hostID, locale, localeCapacity, status);
}
int32_t uloc_getName(const char *localeID, char *name, int32_t nameCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getName)(localeID, name, nameCapacity, err);
}
int32_t uloc_getParent(const char *localeID, char *parent, int32_t parentCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getParent)(localeID, parent, parentCapacity, err);
}
int32_t uloc_getScript(const char *localeID, char *script, int32_t scriptCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getScript)(localeID, script, scriptCapacity, err);
}
int32_t uloc_getVariant(const char *localeID, char *variant, int32_t variantCapacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_getVariant)(localeID, variant, variantCapacity, err);
}
UBool uloc_isRightToLeft(const char *locale)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_isRightToLeft)(locale);
}
int32_t uloc_minimizeSubtags(const char *localeID, char *minimizedLocaleID, int32_t minimizedLocaleIDCapacity,
                             UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_minimizeSubtags)(localeID, minimizedLocaleID, minimizedLocaleIDCapacity, err);
}
UEnumeration *uloc_openAvailableByType(ULocAvailableType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_openAvailableByType)(type, status);
}
UEnumeration *uloc_openKeywords(const char *localeID, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_openKeywords)(localeID, status);
}
void uloc_setDefault(const char * localeID, UErrorCode * status)
{
#ifdef ICU_SUPPORT_LIBBEGETUTIL
  g_isCustomLocale = true;
#endif
  U_ICU_ENTRY_POINT_RENAME(uloc_setDefault)(localeID, status);
}
int32_t uloc_setKeywordValue(const char *keywordName, const char *keywordValue, char *buffer, int32_t bufferCapacity,
                             UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_setKeywordValue)(keywordName, keywordValue, buffer, bufferCapacity, status);
}
int32_t uloc_toLanguageTag(const char *localeID, char *langtag, int32_t langtagCapacity, UBool strict, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_toLanguageTag)(localeID, langtag, langtagCapacity, strict, err);
}
const char *uloc_toLegacyKey(const char *keyword)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_toLegacyKey)(keyword);
}
const char *uloc_toLegacyType(const char *keyword, const char *value)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_toLegacyType)(keyword, value);
}
const char *uloc_toUnicodeLocaleKey(const char *keyword)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_toUnicodeLocaleKey)(keyword);
}
const char *uloc_toUnicodeLocaleType(const char *keyword, const char *value)
{
    return U_ICU_ENTRY_POINT_RENAME(uloc_toUnicodeLocaleType)(keyword, value);
}
int32_t unorm2_append(const UNormalizer2 *norm2, UChar *first, int32_t firstLength, int32_t firstCapacity,
                      const UChar *second, int32_t secondLength, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_append)(norm2, first, firstLength, firstCapacity, second, secondLength,
                                                   pErrorCode);
}
void unorm2_close(UNormalizer2 *norm2)
{
    U_ICU_ENTRY_POINT_RENAME(unorm2_close)(norm2);
}
UChar32 unorm2_composePair(const UNormalizer2 *norm2, UChar32 a, UChar32 b)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_composePair)(norm2, a, b);
}
uint8_t unorm2_getCombiningClass(const UNormalizer2 *norm2, UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getCombiningClass)(norm2, c);
}
int32_t unorm2_getDecomposition(const UNormalizer2 *norm2, UChar32 c, UChar *decomposition, int32_t capacity,
                                UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getDecomposition)(norm2, c, decomposition, capacity, pErrorCode);
}
const UNormalizer2 *unorm2_getInstance(const char *packageName, const char *name, UNormalization2Mode mode,
                                       UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getInstance)(packageName, name, mode, pErrorCode);
}
const UNormalizer2 *unorm2_getNFCInstance(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getNFCInstance)(pErrorCode);
}
const UNormalizer2 *unorm2_getNFDInstance(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getNFDInstance)(pErrorCode);
}
const UNormalizer2 *unorm2_getNFKCCasefoldInstance(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getNFKCCasefoldInstance)(pErrorCode);
}
const UNormalizer2 *unorm2_getNFKCInstance(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getNFKCInstance)(pErrorCode);
}
const UNormalizer2 *unorm2_getNFKDInstance(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getNFKDInstance)(pErrorCode);
}
int32_t unorm2_getRawDecomposition(const UNormalizer2 *norm2, UChar32 c, UChar *decomposition, int32_t capacity,
                                   UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_getRawDecomposition)(norm2, c, decomposition, capacity, pErrorCode);
}
UBool unorm2_hasBoundaryAfter(const UNormalizer2 *norm2, UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_hasBoundaryAfter)(norm2, c);
}
UBool unorm2_hasBoundaryBefore(const UNormalizer2 *norm2, UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_hasBoundaryBefore)(norm2, c);
}
UBool unorm2_isInert(const UNormalizer2 *norm2, UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_isInert)(norm2, c);
}
UBool unorm2_isNormalized(const UNormalizer2 *norm2, const UChar *s, int32_t length, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_isNormalized)(norm2, s, length, pErrorCode);
}
int32_t unorm2_normalize(const UNormalizer2 *norm2, const UChar *src, int32_t length, UChar *dest, int32_t capacity,
                         UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_normalize)(norm2, src, length, dest, capacity, pErrorCode);
}
int32_t unorm2_normalizeSecondAndAppend(const UNormalizer2 *norm2, UChar *first, int32_t firstLength,
                                        int32_t firstCapacity, const UChar *second, int32_t secondLength,
                                        UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_normalizeSecondAndAppend)(norm2, first, firstLength, firstCapacity, second,
                                                                     secondLength, pErrorCode);
}
UNormalizer2 *unorm2_openFiltered(const UNormalizer2 *norm2, const USet *filterSet, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_openFiltered)(norm2, filterSet, pErrorCode);
}
UNormalizationCheckResult unorm2_quickCheck(const UNormalizer2 *norm2, const UChar *s, int32_t length,
                                            UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_quickCheck)(norm2, s, length, pErrorCode);
}
int32_t unorm2_spanQuickCheckYes(const UNormalizer2 *norm2, const UChar *s, int32_t length, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm2_spanQuickCheckYes)(norm2, s, length, pErrorCode);
}
int32_t unorm_compare(const UChar *s1, int32_t length1, const UChar *s2, int32_t length2, uint32_t options,
                      UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(unorm_compare)(s1, length1, s2, length2, options, pErrorCode);
}
void unum_applyPattern(UNumberFormat *format, UBool localized, const UChar *pattern, int32_t patternLength,
                       UParseError *parseError, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(unum_applyPattern)(format, localized, pattern, patternLength, parseError, status);
}
UNumberFormat *unum_clone(const UNumberFormat *fmt, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_clone)(fmt, status);
}
void unum_close(UNumberFormat *fmt)
{
    U_ICU_ENTRY_POINT_RENAME(unum_close)(fmt);
}
int32_t unum_countAvailable()
{
    return U_ICU_ENTRY_POINT_RENAME(unum_countAvailable)();
}
int32_t unum_format(const UNumberFormat *fmt, int32_t number, UChar *result, int32_t resultLength, UFieldPosition *pos,
                    UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_format)(fmt, number, result, resultLength, pos, status);
}
int32_t unum_formatDecimal(const UNumberFormat *fmt, const char *number, int32_t length, UChar *result,
                           int32_t resultLength, UFieldPosition *pos, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_formatDecimal)(fmt, number, length, result, resultLength, pos, status);
}
int32_t unum_formatDouble(const UNumberFormat *fmt, double number, UChar *result, int32_t resultLength,
                          UFieldPosition *pos, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_formatDouble)(fmt, number, result, resultLength, pos, status);
}
int32_t unum_formatDoubleCurrency(const UNumberFormat *fmt, double number, UChar *currency, UChar *result,
                                  int32_t resultLength, UFieldPosition *pos, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_formatDoubleCurrency)(fmt, number, currency, result, resultLength, pos,
                                                               status);
}
int32_t unum_formatDoubleForFields(const UNumberFormat *format, double number, UChar *result, int32_t resultLength,
                                   UFieldPositionIterator *fpositer, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_formatDoubleForFields)(format, number, result, resultLength, fpositer, status);
}
int32_t unum_formatInt64(const UNumberFormat *fmt, int64_t number, UChar *result, int32_t resultLength,
                         UFieldPosition *pos, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_formatInt64)(fmt, number, result, resultLength, pos, status);
}
int32_t unum_getAttribute(const UNumberFormat *fmt, UNumberFormatAttribute attr)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getAttribute)(fmt, attr);
}
const char *unum_getAvailable(int32_t localeIndex)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getAvailable)(localeIndex);
}
UDisplayContext unum_getContext(const UNumberFormat *fmt, UDisplayContextType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getContext)(fmt, type, status);
}
double unum_getDoubleAttribute(const UNumberFormat *fmt, UNumberFormatAttribute attr)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getDoubleAttribute)(fmt, attr);
}
const char *unum_getLocaleByType(const UNumberFormat *fmt, ULocDataLocaleType type, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getLocaleByType)(fmt, type, status);
}
int32_t unum_getSymbol(const UNumberFormat *fmt, UNumberFormatSymbol symbol, UChar *buffer, int32_t size,
                       UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getSymbol)(fmt, symbol, buffer, size, status);
}
int32_t unum_getTextAttribute(const UNumberFormat *fmt, UNumberFormatTextAttribute tag, UChar *result,
                              int32_t resultLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_getTextAttribute)(fmt, tag, result, resultLength, status);
}
UNumberFormat *unum_open(UNumberFormatStyle style, const UChar *pattern, int32_t patternLength, const char *locale,
                         UParseError *parseErr, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_open)(style, pattern, patternLength, locale, parseErr, status);
}
int32_t unum_parse(const UNumberFormat *fmt, const UChar *text, int32_t textLength, int32_t *parsePos,
                   UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_parse)(fmt, text, textLength, parsePos, status);
}
int32_t unum_parseDecimal(const UNumberFormat *fmt, const UChar *text, int32_t textLength, int32_t *parsePos,
                          char *outBuf, int32_t outBufLength, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_parseDecimal)(fmt, text, textLength, parsePos, outBuf, outBufLength, status);
}
double unum_parseDouble(const UNumberFormat *fmt, const UChar *text, int32_t textLength, int32_t *parsePos,
                        UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_parseDouble)(fmt, text, textLength, parsePos, status);
}
double unum_parseDoubleCurrency(const UNumberFormat *fmt, const UChar *text, int32_t textLength, int32_t *parsePos,
                                UChar *currency, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_parseDoubleCurrency)(fmt, text, textLength, parsePos, currency, status);
}
int64_t unum_parseInt64(const UNumberFormat *fmt, const UChar *text, int32_t textLength, int32_t *parsePos,
                        UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_parseInt64)(fmt, text, textLength, parsePos, status);
}
void unum_setAttribute(UNumberFormat *fmt, UNumberFormatAttribute attr, int32_t newValue)
{
    U_ICU_ENTRY_POINT_RENAME(unum_setAttribute)(fmt, attr, newValue);
}
void unum_setContext(UNumberFormat *fmt, UDisplayContext value, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(unum_setContext)(fmt, value, status);
}
void unum_setDoubleAttribute(UNumberFormat *fmt, UNumberFormatAttribute attr, double newValue)
{
    U_ICU_ENTRY_POINT_RENAME(unum_setDoubleAttribute)(fmt, attr, newValue);
}
void unum_setSymbol(UNumberFormat *fmt, UNumberFormatSymbol symbol, const UChar *value, int32_t length,
                    UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(unum_setSymbol)(fmt, symbol, value, length, status);
}
void unum_setTextAttribute(UNumberFormat *fmt, UNumberFormatTextAttribute tag, const UChar *newValue,
                           int32_t newValueLength, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(unum_setTextAttribute)(fmt, tag, newValue, newValueLength, status);
}
int32_t unum_toPattern(const UNumberFormat *fmt, UBool isPatternLocalized, UChar *result, int32_t resultLength,
                       UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(unum_toPattern)(fmt, isPatternLocalized, result, resultLength, status);
}
void unumf_close(UNumberFormatter *uformatter)
{
    U_ICU_ENTRY_POINT_RENAME(unumf_close)(uformatter);
}
void unumf_formatDecimal(const UNumberFormatter *uformatter, const char *value, int32_t valueLen,
                         UFormattedNumber *uresult, UErrorCode *ec)
{
    U_ICU_ENTRY_POINT_RENAME(unumf_formatDecimal)(uformatter, value, valueLen, uresult, ec);
}
void unumf_formatDouble(const UNumberFormatter *uformatter, double value, UFormattedNumber *uresult, UErrorCode *ec)
{
    U_ICU_ENTRY_POINT_RENAME(unumf_formatDouble)(uformatter, value, uresult, ec);
}
void unumf_formatInt(const UNumberFormatter *uformatter, int64_t value, UFormattedNumber *uresult, UErrorCode *ec)
{
    U_ICU_ENTRY_POINT_RENAME(unumf_formatInt)(uformatter, value, uresult, ec);
}
UNumberFormatter *unumf_openForSkeletonAndLocale(const UChar *skeleton, int32_t skeletonLen, const char *locale,
                                                 UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(unumf_openForSkeletonAndLocale)(skeleton, skeletonLen, locale, ec);
}
UNumberFormatter *unumf_openForSkeletonAndLocaleWithError(const UChar *skeleton, int32_t skeletonLen,
                                                          const char *locale, UParseError *perror, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(unumf_openForSkeletonAndLocaleWithError)(skeleton, skeletonLen, locale, perror,
                                    ec);
}
UBool uscript_breaksBetweenLetters(UScriptCode script)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_breaksBetweenLetters)(script);
}
int32_t uscript_getCode(const char *nameOrAbbrOrLocale, UScriptCode *fillIn, int32_t capacity, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getCode)(nameOrAbbrOrLocale, fillIn, capacity, err);
}
const char *uscript_getName(UScriptCode scriptCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getName)(scriptCode);
}
int32_t uscript_getSampleString(UScriptCode script, UChar *dest, int32_t capacity, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getSampleString)(script, dest, capacity, pErrorCode);
}
UScriptCode uscript_getScript(UChar32 codepoint, UErrorCode *err)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getScript)(codepoint, err);
}
int32_t uscript_getScriptExtensions(UChar32 c, UScriptCode *scripts, int32_t capacity, UErrorCode *errorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getScriptExtensions)(c, scripts, capacity, errorCode);
}
const char *uscript_getShortName(UScriptCode scriptCode)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getShortName)(scriptCode);
}
UScriptUsage uscript_getUsage(UScriptCode script)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_getUsage)(script);
}
UBool uscript_hasScript(UChar32 c, UScriptCode sc)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_hasScript)(c, sc);
}
UBool uscript_isCased(UScriptCode script)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_isCased)(script);
}
UBool uscript_isRightToLeft(UScriptCode script)
{
    return U_ICU_ENTRY_POINT_RENAME(uscript_isRightToLeft)(script);
}
void uset_add(USet *set, UChar32 c)
{
    U_ICU_ENTRY_POINT_RENAME(uset_add)(set, c);
}
void uset_addString(USet *set, const UChar *str, int32_t strLen)
{
    U_ICU_ENTRY_POINT_RENAME(uset_addString)(set, str, strLen);
}
void uset_clear(USet *set)
{
    U_ICU_ENTRY_POINT_RENAME(uset_clear)(set);
}
void uset_close(USet *set)
{
    U_ICU_ENTRY_POINT_RENAME(uset_close)(set);
}
void uset_complement(USet *set)
{
    U_ICU_ENTRY_POINT_RENAME(uset_complement)(set);
}
UBool uset_contains(const USet *set, UChar32 c)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_contains)(set, c);
}
UBool uset_containsString(const USet *set, const UChar *str, int32_t strLen)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_containsString)(set, str, strLen);
}
int32_t uset_getItem(const USet *set, int32_t itemIndex, UChar32 *start, UChar32 *end, UChar *str, int32_t strCapacity,
                     UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_getItem)(set, itemIndex, start, end, str, strCapacity, ec);
}
int32_t uset_getItemCount(const USet *set)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_getItemCount)(set);
}
int32_t uset_getRangeCount(const USet *set)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_getRangeCount)(set);
}
UBool uset_isEmpty(const USet *set)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_isEmpty)(set);
}
USet *uset_open(UChar32 start, UChar32 end)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_open)(start, end);
}
USet *uset_openPattern(const UChar *pattern, int32_t patternLength, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_openPattern)(pattern, patternLength, ec);
}
USet *uset_openPatternOptions(const UChar *pattern, int32_t patternLength, uint32_t options, UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_openPatternOptions)(pattern, patternLength, options, ec);
}
void uset_remove(USet *set, UChar32 c)
{
    U_ICU_ENTRY_POINT_RENAME(uset_remove)(set, c);
}
void uset_removeString(USet *set, const UChar *str, int32_t strLen)
{
    U_ICU_ENTRY_POINT_RENAME(uset_removeString)(set, str, strLen);
}
int32_t uset_size(const USet *set)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_size)(set);
}
int32_t uset_toPattern(const USet *set, UChar *result, int32_t resultCapacity, UBool escapeUnprintable,
                       UErrorCode *ec)
{
    return U_ICU_ENTRY_POINT_RENAME(uset_toPattern)(set, result, resultCapacity, escapeUnprintable, ec);
}
UTransliterator *utrans_clone(const UTransliterator *trans, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_clone)(trans, status);
}
void utrans_close(UTransliterator *trans)
{
    U_ICU_ENTRY_POINT_RENAME(utrans_close)(trans);
}
int32_t utrans_countAvailableIDs()
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_countAvailableIDs)();
}
USet *utrans_getSourceSet(const UTransliterator *trans, UBool ignoreFilter, USet *fillIn, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_getSourceSet)(trans, ignoreFilter, fillIn, status);
}
const UChar *utrans_getUnicodeID(const UTransliterator *trans, int32_t *resultLength)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_getUnicodeID)(trans, resultLength);
}
UEnumeration *utrans_openIDs(UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_openIDs)(pErrorCode);
}
UTransliterator *utrans_openInverse(const UTransliterator *trans, UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_openInverse)(trans, status);
}
UTransliterator *utrans_openU(const UChar *id, int32_t idLength, UTransDirection dir, const UChar *rules,
                              int32_t rulesLength, UParseError *parseError, UErrorCode *pErrorCode)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_openU)(id, idLength, dir, rules, rulesLength, parseError, pErrorCode);
}
void utrans_register(UTransliterator *adoptedTrans, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(utrans_register)(adoptedTrans, status);
}
void utrans_setFilter(UTransliterator *trans, const UChar *filterPattern, int32_t filterPatternLen,
                      UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(utrans_setFilter)(trans, filterPattern, filterPatternLen, status);
}
int32_t utrans_toRules(const UTransliterator *trans, UBool escapeUnprintable, UChar *result, int32_t resultLength,
                       UErrorCode *status)
{
    return U_ICU_ENTRY_POINT_RENAME(utrans_toRules)(trans, escapeUnprintable, result, resultLength, status);
}
void utrans_transIncrementalUChars(const UTransliterator *trans, UChar *text, int32_t *textLength, int32_t textCapacity,
                                   UTransPosition *pos, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(utrans_transIncrementalUChars)(trans, text, textLength, textCapacity, pos, status);
}
void utrans_transUChars(const UTransliterator *trans, UChar *text, int32_t *textLength, int32_t textCapacity,
                        int32_t start, int32_t *limit, UErrorCode *status)
{
    U_ICU_ENTRY_POINT_RENAME(utrans_transUChars)(trans, text, textLength, textCapacity, start, limit, status);
}
void utrans_unregisterID(const UChar *id, int32_t idLength)
{
    U_ICU_ENTRY_POINT_RENAME(utrans_unregisterID)(id, idLength);
}
}