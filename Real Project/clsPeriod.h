#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsPeriod
{

    private:
    clsDate StartDate;
    clsDate EndDate;

    public:
    clsPeriod(clsDate DateFrom,clsDate DateTo)
    {
        this->StartDate = DateFrom;
        this->EndDate = DateTo;
    }
    static bool IsOverlapDates(clsPeriod Period1,clsPeriod Period2)
    {
    if
    (
        clsDate::CompareDates(Period2.EndDate,Period1.StartDate) == clsDate::Before
        ||
        clsDate::CompareDates(Period2.StartDate,Period1.EndDate) == clsDate::After
    ) 
        return false;
    else
    return true;
    }
    bool IsOverlapDates(clsPeriod Period2)
    {
        return IsOverlapDates(*this,Period2);
    }

    static short CountPeriodDays(clsPeriod Period1,bool IncludedLastDay = false)
    {
    short Counter = 0;

    while(clsDate::CompareDates(Period1.StartDate,Period1.EndDate)== clsDate::Before)
    {
        Counter ++;
        Period1.StartDate = clsDate::IncreaseDateByOneDay(Period1.StartDate);
    }
    return IncludedLastDay? ++Counter : Counter;
    }
    short CountPeriodDays(bool IncludedLastDay = false)
    {
        return CountPeriodDays(*this,IncludedLastDay);
    }

    static bool IsDateWithinAPeriod(clsPeriod Period,clsDate Date)
    {
    return  !(clsDate::CompareDates(Date,Period.StartDate)==clsDate::Before || clsDate::CompareDates(Date,Period.EndDate) == clsDate::After);
    }
    bool IsDateWithinAPeriod(clsDate Date)
    {
        return IsDateWithinAPeriod(*this,Date);
    }


    static short CountOverlapDates(clsPeriod Period1,clsPeriod Period2)
    {

    int Period1Length = CountPeriodDays(Period1,true);
    int Period2Length = CountPeriodDays(Period2,true);
    int OverlapDays = 0;

    if(!IsOverlapDates(Period1,Period2))
    {
        return 0;
    }

    if(Period1Length<Period2Length)
    {
        while(clsDate::IsDate1BeforeDate2(Period1.StartDate,Period1.EndDate))
        {
            if(IsDateWithinAPeriod(Period2,Period1.StartDate))
            {
                OverlapDays++;
            }

            Period1.StartDate = clsDate::IncreaseDateByOneDay(Period1.StartDate);
        }
    }
    else
    {
        while(clsDate::IsDate1BeforeDate2(Period2.StartDate,Period2.EndDate))
        {
            if(IsDateWithinAPeriod(Period1,Period2.StartDate))
            {
                OverlapDays++;
            }

            Period2.StartDate = clsDate::IncreaseDateByOneDay(Period2.StartDate);
        }
    }

    return OverlapDays;

}



};

