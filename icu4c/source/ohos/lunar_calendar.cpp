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
#include "lunar_calendar.h"


namespace OHOS {
namespace ICU {
const std::string LunarCalendar::LunarType = "chinese";
static const int32_t CYCLE_LENGTH = 60;
static const int32_t CHINESE_EPOCH_YEAR = -2636;
static const int32_t LUNAR1900_TO_SOLAR1970 = 25538;

static const std::vector<int32_t> daysOfMonth { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static const std::vector<int32_t> accDaysOfMonth {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

static const std::vector<uint32_t> lunarDateInfo {
    0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2,
    0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977,
    0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970,
    0x06566, 0x0d4a0, 0x0ea50, 0x16a95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950,
    0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557,
    0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5b0, 0x14573, 0x052b0, 0x0a9a8, 0x0e950, 0x06aa0,
    0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0,
    0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b6a0, 0x195a6,
    0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570,
    0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x05ac0, 0x0ab60, 0x096d5, 0x092e0,
    0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5,
    0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930,
    0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530,
    0x05aa0, 0x076a3, 0x096d0, 0x04afb, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45,
    0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0,
    0x14b63, 0x09370, 0x049f8, 0x04970, 0x064b0, 0x168a6, 0x0ea50, 0x06aa0, 0x1a6c4, 0x0aae0,
    0x092e0, 0x0d2e3, 0x0c960, 0x0d557, 0x0d4a0, 0x0da50, 0x05d55, 0x056a0, 0x0a6d0, 0x055d4,
    0x052d0, 0x0a9b8, 0x0a950, 0x0b4a0, 0x0b6a6, 0x0ad50, 0x055a0, 0x0aba4, 0x0a5b0, 0x052b0,
    0x0b273, 0x06930, 0x07337, 0x06aa0, 0x0ad50, 0x14b55, 0x04b60, 0x0a570, 0x054e4, 0x0d160,
    0x0e968, 0x0d520, 0x0daa0, 0x16aa6, 0x056d0, 0x04ae0, 0x0a9d4, 0x0a2d0, 0x0d150, 0x0f252,
    0x0d520,
};

int32_t LunarCalendar::GetLeapDaysInYear(int32_t year)
{
    if ((year < VALID_START_YEAR) || (year > VALID_END_YEAR)) {
        return -1;
    }
    if (GetLeapMonthInYear(year) != 0) {
        return (lunarDateInfo[year - START_YEAR] & 0x10000) == 0x10000 ? DAYS_IN_BIG_MONTH : DAYS_IN_SMALL_MONTH;
      }
      return 0;
}

int32_t LunarCalendar::GetLeapMonthInYear(int32_t year)
{
    if ((year < VALID_START_YEAR) || (year > VALID_END_YEAR)) {
        return -1;
    }
    return lunarDateInfo[year - START_YEAR] & 0xf;
}

int32_t LunarCalendar::GetDaysInMonth(int32_t year, int32_t month)
{
    if ((year < VALID_START_YEAR) || (year > VALID_END_YEAR)) {
        return -1;
    }
    if ((month > VALID_END_MONTH) || (month < VALID_START_MONTH)) {
        return -1;
    }
    uint32_t offset = 0x10000 >> static_cast<uint32_t>(month);
    return (lunarDateInfo[year - START_YEAR] & offset) == offset ? DAYS_IN_BIG_MONTH : DAYS_IN_SMALL_MONTH;
}

LunarCalendar::LunarCalendar()
{
}

LunarCalendar::~LunarCalendar()
{
}

bool LunarCalendar::SetDaysFrom1970(int32_t year, int32_t month, int32_t daysFrom1970)
{
    int32_t day = daysFrom1970 + CalcDaysFromBaseDate(1970, 1, 1) - CalcDaysFromBaseDate(year, month, 1) + 1;
    isGregorianLeapYear = false;
    isValidDate = VerifyDate(year, month, day);
    if (!isValidDate) {
        return false;
    }
    solarYear = year;
    solarMonth = month;
    solarDay = day;
    daysCounts = CalcDaysFromBaseDate(solarYear, solarMonth, solarDay);
    SolarDateToLunarDate();
    return true;
}

int32_t LunarCalendar::CalcDaysFromBaseDate(int32_t year, int32_t month, int32_t day)
{
    int32_t daysNum = DAYS_OF_YEAR * (year - START_YEAR);
    daysNum += accDaysOfMonth[month - 1];
    bool isLeapYear = IsGregorianLeapYear(year);
    if (isLeapYear && month > MONTH_FEB) {
        daysNum++;
    }
    daysNum--;
    daysNum += day;
    daysNum += (year - START_YEAR) / FREQ_LEAP_YEAR;
    if (isLeapYear) {
        daysNum--;
    }
    if (year >= VALID_END_YEAR) {
        daysNum--;
    }
    return daysNum;
}

void LunarCalendar::SolarDateToLunarDate()
{
    int32_t daysInPerLunarYear = 0;
    int32_t daysInPerLunarMonth = 0;
    int tempDaysCounts = daysCounts;
    tempDaysCounts -= DAYS_FROM_SOLAR_TO_LUNAR;
    int32_t i = 0;
    for (i = START_YEAR; (tempDaysCounts > 0) && (i < END_YEAR); i++) {
        daysInPerLunarYear = GetDaysPerLunarYear(i);
        tempDaysCounts -= daysInPerLunarYear;
    }
    if (tempDaysCounts < 0) {
        tempDaysCounts += daysInPerLunarYear;
        --i;
    }
    lunarYear = i;

    leapMonth = GetLeapMonthInYear(lunarYear);
    isLeapMonth = false;
    for (i = 1; i <= VALID_END_MONTH && tempDaysCounts > 0; i++) {
        if (leapMonth > 0 && (leapMonth + 1) == i && !isLeapMonth) {
            --i;
            isLeapMonth = true;
            daysInPerLunarMonth = GetLeapDaysInYear(lunarYear);
        } else {
            daysInPerLunarMonth = GetDaysInMonth(lunarYear, i);
        }
        if (isLeapMonth && (leapMonth + 1) == i) {
            isLeapMonth = false;
        }
        tempDaysCounts -= daysInPerLunarMonth;
    }
    AdjustLeapMonth(i, tempDaysCounts, leapMonth);
    if (tempDaysCounts < 0) {
        tempDaysCounts += daysInPerLunarMonth;
        --i;
    }
    lunarMonth = i;
    lunarDay = tempDaysCounts + 1;
}

void LunarCalendar::AdjustLeapMonth(int32_t& i, int32_t tempDaysCounts, int32_t month)
{
    if (tempDaysCounts == 0 && month > 0 && i == month + 1) {
        if (isLeapMonth) {
            isLeapMonth = false;
        } else {
            isLeapMonth = true;
            --i;
        }
    }
}

int32_t LunarCalendar::GetDaysPerLunarYear(int32_t year)
{
    int32_t daysPerLunarYear = 0;
    if ((year < START_YEAR) || (year > END_YEAR)) {
        return 0;
    }
    daysPerLunarYear += BASE_DAYS_PER_LUNAR_YEAR;
    for (uint32_t i = 0x8000; i > 0x8; i = i >> 1) {
        daysPerLunarYear += ((lunarDateInfo[year - START_YEAR] & i) == i) ? 1 : 0;
    }
    daysPerLunarYear += GetLeapDaysInYear(year);
    return daysPerLunarYear;
}

bool LunarCalendar::VerifyDate(int32_t year, int32_t month, int32_t day)
{
    if ((year < VALID_START_YEAR) || (year > VALID_END_YEAR)) {
        return false;
    }

    if ((month < VALID_START_MONTH) || (month > VALID_END_MONTH)) {
        return false;
    }

    int32_t validEndDay = daysOfMonth[month - 1];
    isGregorianLeapYear = IsGregorianLeapYear(year);
    if (month == MONTH_FEB) {
        validEndDay = isGregorianLeapYear ? validEndDay + 1 : validEndDay;
    }

    if ((day < VALID_START_DAY) || (day > validEndDay)) {
        return false;
    }
    return true;
}

bool LunarCalendar::IsGregorianLeapYear(int32_t year)
{
    if (year % YEAR_ERA == 0) {
        if (year % (YEAR_ERA * FREQ_LEAP_YEAR) == 0) {
            return true;
        }
        return false;
    }
    if (year % FREQ_LEAP_YEAR == 0) {
        return true;
    }
    return false;
}

int32_t LunarCalendar::GetSolarYear()
{
    if (!isValidDate) {
        return -1;
    }
    return solarYear;
}

int32_t LunarCalendar::GetSolarMonth()
{
    if (!isValidDate) {
        return -1;
    }
    return solarMonth;
}

int32_t LunarCalendar::GetSolarDay()
{
    if (!isValidDate) {
        return -1;
    }
    return solarDay;
}

int32_t LunarCalendar::GetLunarYear()
{
    if (!isValidDate) {
        return -1;
    }
    return lunarYear;
}

int32_t LunarCalendar::GetLunarMonth()
{
    if (!isValidDate) {
        return -1;
    }
    return lunarMonth;
}

int32_t LunarCalendar::GetLunarDay()
{
    if (!isValidDate) {
        return -1;
    }
    return lunarDay;
}

bool LunarCalendar::IsLeapMonth()
{
    if (!isValidDate) {
        return false;
    }
    return isLeapMonth;
}

int32_t LunarCalendar::GetEra()
{
    if (!isValidDate) {
        return -1;
    }

    int32_t diffYears = (lunarYear - CHINESE_EPOCH_YEAR + 1) % CYCLE_LENGTH;
    int era = (lunarYear - CHINESE_EPOCH_YEAR + 1) / CYCLE_LENGTH;
    return (diffYears == 0) ? era : era + 1;
}

int32_t LunarCalendar::GetCycleYear()
{
    if (!isValidDate) {
        return -1;
    }

    int32_t diffYears = (lunarYear - CHINESE_EPOCH_YEAR + 1) % CYCLE_LENGTH;
    return (diffYears == 0) ? CYCLE_LENGTH : diffYears;
}

int32_t LunarCalendar::GetDateOfYear()
{
    if (!isValidDate) {
        return -1;
    }
    int32_t lunarDayOfYear = 0;

    for (int32_t month = 1; month < lunarMonth; ++month) {
        lunarDayOfYear += GetDaysInMonth(lunarYear, month);
    }

    if (leapMonth > 0) {
        if (lunarMonth > leapMonth){
            lunarDayOfYear += GetLeapDaysInYear(lunarYear);
        } else if (isLeapMonth && (lunarMonth == leapMonth)) {
            lunarDayOfYear += GetDaysInMonth(lunarYear, lunarMonth);
        }
    }
    lunarDayOfYear += lunarDay;
    return lunarDayOfYear;
}

int32_t LunarCalendar::GetOrdinalMonth()
{
    if (!isValidDate) {
        return -1;
    }
    if (leapMonth == 0) {
        return lunarMonth;
    }
    if (isLeapMonth) {
        return leapMonth + 1;
    } else if (lunarMonth > leapMonth) {
        return lunarMonth + 1;
    } else {
        return lunarMonth;
    }
}

int32_t LunarCalendar::GetExtendedYear()
{
    if (!isValidDate) {
        return -1;
    }
    return lunarYear - CHINESE_EPOCH_YEAR + 1;
}

int32_t LunarCalendar::NewYear(int32_t eyear)
{
    int32_t lyear = eyear + CHINESE_EPOCH_YEAR - 1;
    if (lyear < START_YEAR || lyear >= END_YEAR) {
        return -1;
    }

    int32_t daysNum = 0;
    for (int32_t i = START_YEAR; i < lyear; i++) {
        daysNum += GetDaysPerLunarYear(i);
    }
    
    return daysNum + 1 - LUNAR1900_TO_SOLAR1970;
}

int32_t LunarCalendar::NewMoonNear(int32_t days)
{
    int32_t daysNum = days + LUNAR1900_TO_SOLAR1970 - 1;
    int32_t year = START_YEAR;
    for (; year < END_YEAR && daysNum >= GetDaysPerLunarYear(year); year++) {
        daysNum -= GetDaysPerLunarYear(year);
    }
    if (year >= END_YEAR || year < START_YEAR) {
        return -1;
    }
    
    int32_t leapMonthInYear = GetLeapMonthInYear(year);
    bool isLeapMonthInYear = false;
    int32_t daysInPerLunarMonth = 0;
    int32_t nearestNewMoon = 0;
    for (int32_t i = 1; i <= VALID_END_MONTH && daysNum > 0; i++) {
        if (leapMonthInYear > 0 && (leapMonthInYear + 1) == i && !isLeapMonthInYear) {
            --i;
            isLeapMonthInYear = true;
            daysInPerLunarMonth = GetLeapDaysInYear(year);
        } else {
            daysInPerLunarMonth = GetDaysInMonth(year, i);
        }
        if (isLeapMonthInYear && (leapMonthInYear + 1) == i) {
            isLeapMonthInYear = false;
        }
        daysNum -= daysInPerLunarMonth;
        nearestNewMoon += daysInPerLunarMonth;
    }

    int32_t totalNewMoonDays = 0;
    for (int32_t i = START_YEAR; i < year; i++) {
        totalNewMoonDays += GetDaysPerLunarYear(i);
    }
    totalNewMoonDays += nearestNewMoon;
    
    return totalNewMoonDays + 1 - LUNAR1900_TO_SOLAR1970;
}
} // namespace ICU
} // namespace OHOS