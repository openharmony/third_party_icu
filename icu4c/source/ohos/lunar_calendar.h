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
#ifndef OHOS_GLOBAL_I18N_LUNAR_CALENDAR_H
#define OHOS_GLOBAL_I18N_LUNAR_CALENDAR_H

#include <string>
#include <unordered_map>
#include <vector>

namespace OHOS {
namespace ICU {
class LunarCalendar {
public:
    static int32_t NewYear(int32_t eyear);
    static int32_t NewMoonNear(int32_t days);
    static const std::string LunarType;

    LunarCalendar();
    ~LunarCalendar();
    bool SetDaysFrom1970(int32_t year, int32_t month, int32_t day);
    int32_t GetSolarYear();
    int32_t GetSolarMonth();
    int32_t GetSolarDay();
    int32_t GetLunarYear();
    int32_t GetLunarMonth();
    int32_t GetLunarDay();
    int32_t GetEra();
    int32_t GetCycleYear();
    int32_t GetDateOfYear();
    int32_t GetOrdinalMonth();
    int32_t GetExtendedYear();
    bool IsLeapMonth();

private:
    static int32_t GetDaysPerLunarYear(int32_t year);
    static bool IsGregorianLeapYear(int32_t year);
    static int32_t GetLeapDaysInYear(int32_t year);
    static int32_t GetLeapMonthInYear(int32_t year);
    static int32_t GetDaysInMonth(int32_t year, int32_t month);

    bool VerifyDate(int32_t year, int32_t month, int32_t day);
    int32_t CalcDaysFromBaseDate(int32_t year, int32_t month, int32_t day);
    void SolarDateToLunarDate();
    void AdjustLeapMonth(int32_t& i, int32_t tempDaysCounts, int32_t month);
    static const int32_t VALID_START_YEAR = 1900;
    static const int32_t VALID_END_YEAR = 2100;
    static const int32_t VALID_START_MONTH = 1;
    static const int32_t VALID_END_MONTH = 12;
    static const int32_t VALID_START_DAY = 1;
    static const int32_t MONTH_FEB = 2;
    static const int32_t START_YEAR = 1900;
    static const int32_t END_YEAR = 2100;
    static const int32_t DAYS_OF_YEAR = 365;
    static const int32_t YEAR_ERA = 100;
    static const int32_t FREQ_LEAP_YEAR = 4;
    static const int32_t DAYS_FROM_SOLAR_TO_LUNAR = 30;
    static const int32_t BASE_DAYS_PER_LUNAR_YEAR = 348;
    static const int32_t DAYS_IN_BIG_MONTH = 30;
    static const int32_t DAYS_IN_SMALL_MONTH = 29;

    int32_t solarYear = -1;
    int32_t solarMonth = -1;
    int32_t solarDay = -1;
    int32_t lunarYear = -1;
    int32_t lunarMonth = -1;
    int32_t lunarDay = -1;
    int32_t daysCounts = 0;
    int32_t leapMonth = 0;
    bool isLeapMonth = false;
    bool isGregorianLeapYear = false;
    bool isValidDate = false;
};
} // namespace ICU
} // namespace OHOS
#endif