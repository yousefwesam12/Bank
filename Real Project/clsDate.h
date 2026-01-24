#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"
using namespace std;

class clsDate
{
    private:
    short Day;
    short Month;
    short Year;

    public:
    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        this->Year = now->tm_year + 1900;
        this->Month = now->tm_mon + 1;
        this->Day = now->tm_mday;
    }
    clsDate(short Day,short Month,short Year)
    {
        this->Day   = Day;
        this->Month = Month;
        this->Year  = Year;
    }
    clsDate(string Date)
    {
        vector <string> vDate = clsString::Split(Date,"/");

        this->Day = stoi(vDate[0]);
        this->Month = stoi(vDate[1]);
        this->Year = stoi(vDate[2]);
    }
    clsDate(short DateOrderInYear,short Year)
    {
        clsDate Date1 = GetDateFromDayOrder(DateOrderInYear,Year);

        this->Day = Date1.Day;
        this->Month = Date1.Month;
        this->Year = Date1.Year;
    }
    void SetDay(short Day)
    {
        this->Day = Day;
    }
    short GetDay()
    {
        return this->Day;
    }
    
    void SetMonth(short Month)
    {
        this->Month = Month;
    }
    short GetMonth()
    {
        return this->Month;
    }
    
    void SetYear(short Year)
    {
        this->Year = Year;
    }
    short GetYear()
    {
        return this->Year;
    }
    
    void Print()
    {
        cout << DateToString() << endl;
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }
    string DateToString()
    {
        return DateToString(*this);
    }
    
    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day,Month,Year;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;

        return clsDate(Day,Month,Year);
    }
    
    static bool IsValidDate(clsDate Date1)
    {
	 
    if(Date1.Day<1 || Date1.Day>31)
        return false;

    if(Date1.Month<1||Date1.Month>12)
        return false;

    if(Date1.Month==2)
    {
        if(IsLeapYear(Date1.Year))
        {
            if(Date1.Day>29)
            {
                return false;
            }
        }
        else
        {
            if(Date1.Day>28)
            {
                return false;
            }
        }
    }

    short DaysInMonth = NumberOfDaysInAMonth(Date1.Month,Date1.Year);

    if(Date1.Day>DaysInMonth)
        return false;

    return true;
    }
    bool IsValid()
    {
        return IsValidDate(*this);
    }

    static bool IsLeapYear(short Year)
    {
    return (Year%400 == 0) || (Year%100!=0 && Year % 4==0);
    }
    bool IsLeapYear()
    {
        return IsLeapYear(this->Year);
    }

    static short NumberOfDaysInAMonth(short Year,short Month)
    {
    short NumberOfDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    return (Month==2) ? (IsLeapYear(Year) ? 29 : 28 ) : NumberOfDays[Month-1];
    }
    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(this->Year,this->Month);
    }

    static short NumOfDaysInAYear(short Year)
    {
    return IsLeapYear(Year) ? 366 : 365;
    }
    short NumOfDaysInAYear()
    {
        return NumOfDaysInAYear(this->Year);
    }

    static short NumOfHoursInAYear(short Year)
    {
    return NumOfDaysInAYear(Year) * 24;
    }
    short NumOfHoursInAYear()
    {
        return NumOfHoursInAYear(this->Year);
    }

    static int NumOfMinutesInAYear(short Year)
    {
    return NumOfHoursInAYear(Year) * 60;
    }
    int NumOfMinutesInAYear()
    {
        return NumOfMinutesInAYear(this->Year);
    }

    static long long NumOfSecondsInAYear(short Year)
    {
    return NumOfMinutesInAYear(Year) * 60;
    }
    long long NumOfSecondsInAYear()
    {
        return NumOfSecondsInAYear(this->Year);
    }
 
    static string MonthShortName(short Month)
    {
    string Months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    return Months[Month-1];
    }
    string MonthShortName()
    {
        return MonthShortName(this->Month);
    }

    static void PrintMonthCalender(short Month,short Year)
    {
    short MonthDays = 0;

    short Current = GetDayOrder(Month,Year,1);

    MonthDays = NumberOfDaysInAMonth(Month,Year);

    printf("\n  ______________%s________________\n\n",MonthShortName(Month).c_str());

    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int i = 0;

    for (i = 0;i<Current;++i)
        printf("     ");

    for (int j = 1;j<=MonthDays;j++)
    {
        printf("%5d",j);

        if (++i==7)
        {
            i = 0;
            printf("\n");
        }
    }

    printf("\n ___________________________________");
    }
    void PrintMonthCalender()
    {
        PrintMonthCalender(this->Month,this->Year);
    }

    static void PrintYearCalender(short Year)
    {
    printf("\n  -------------------------------\n");
    printf("\t\t  Calender - %d\n",Year);
    printf("  -------------------------------\n");

    for (int CurrentMonth = 1;CurrentMonth<=12;CurrentMonth++)
    {
        PrintMonthCalender(CurrentMonth,Year);
        cout << endl;

    }

    }
    void PrintYearCalender()
    {
        PrintYearCalender(this->Year);
    }

    static bool IsDate1BeforeDate2(clsDate Date1,clsDate Date2)
    {
    return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }
    bool IsDate1BeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this,Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1,clsDate Date2)
    {
    return  (Date1.Year==Date2.Year) ? ((Date1.Month==Date2.Month) ? (Date1.Day==Date2.Day? true : false) : false) : false;
    }
    bool IsDate1EqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this,Date2);
    }

    static bool IsDate1AfterDate2(clsDate Date1,clsDate Date2)
    {   
    return (!IsDate1BeforeDate2(Date1,Date2) && !IsDate1EqualDate2(Date1,Date2));
    }
    bool IsDate1AfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this,Date2);
    }

    static void SwapDates(clsDate &Date1, clsDate &Date2)
    {
        clsDate TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
    return Date.Day == NumberOfDaysInAMonth(Date.Month,Date.Year);
    }
    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
    return Month == 12;
    }
    bool IsLastMonthInYear()
    {
        return IsLastMonthInYear(this->Month);
    }

    static clsDate IncreaseDateByOneDay(clsDate &Date)
    {
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonthInYear(Date.Month))
        {
            Date.Year++;
            Date.Month = 1;
            Date.Day = 1;
        }
        else
        {
            Date.Day = 1;
            Date.Month++;
        }

    }
    else
    {
        Date.Day++;
    }

    return Date;
    }
    clsDate IncreaseDateByOneDay()
    {
        return IncreaseDateByOneDay(*this);
    }

    static clsDate IncreaseDateByXDays(clsDate &Date,short NumOfDays)
    {
    for (int i = 1;i<=NumOfDays;i++)
        Date = IncreaseDateByOneDay(Date);

        return Date;
    }
    clsDate IncreaseDateByXDays(short NumOfDays)
    {
        return IncreaseDateByXDays(*this,NumOfDays);
    }

    static clsDate IncreaseDateByOneWeek(clsDate &Date)
    {
    for (short i = 1;i<=7;i++)
    {
        Date = IncreaseDateByOneDay(Date);
    }

    return Date;
    }
    clsDate IncreaseDateByOneWeek()
    {
        return IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(clsDate &Date,short NumOfWeeks)
    {
    for (int i = 1;i<=NumOfWeeks;i++)
        Date = IncreaseDateByOneWeek(Date);

    return Date;
    }
    clsDate IncreaseDateByXWeeks(short NumOfWeeks)
    {
        return IncreaseDateByXWeeks(*this,NumOfWeeks);
    }

    static clsDate IncreaseDateByMonth(clsDate &Date)
    {
    if (Date.Month==12)
    {
        Date.Month = 1;
        Date.Year ++;
    }
    else
    {
        Date.Month++;
    }

    short NumOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Year,Date.Month);

    if (Date.Day>NumOfDaysInCurrentMonth)
    {
        Date.Day = NumOfDaysInCurrentMonth;
    }

    return Date;

}
    clsDate IncreaseDateByMonth()
    {
        return IncreaseDateByMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(clsDate &Date,short NumOfMonths)
    {
    for (int i = 1;i<=NumOfMonths;i++)
    {
        Date = IncreaseDateByMonth(Date);
    }
    return Date;
    }
    clsDate IncreaseDateByXMonths(short NumOfMonths)
    {
        return IncreaseDateByXMonths(*this,NumOfMonths);
    }

    static clsDate IncreaseDateByOneYear(clsDate &Date)
    {
    Date.Year++;
    return Date;
    }
    clsDate IncreaseDateByOneYear()
    {
        return IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(clsDate &Date,short NumOfYears)
    {
    for (int i = 1;i<=NumOfYears;i++)
    {
        Date = IncreaseDateByOneYear(Date);
    }

    return Date;
    }
    clsDate IncreaseDateByXYears(short NumOfYears)
    {
        return IncreaseDateByXYears(*this,NumOfYears);
    }

    static clsDate IncreaseDateByXYearsFaster(clsDate &Date,short NumOfYears)
    {
    Date.Year += NumOfYears;
    return Date;
    }
    clsDate IncreaseDateByXYearsFaster(short NumOfYears)
    {
        return IncreaseDateByXYearsFaster(*this,NumOfYears);
    }

    static clsDate IncreaseDateByOneDecade(clsDate &Date)
    {
    Date = IncreaseDateByXYears(Date,10);
    return Date;
    }
    clsDate IncreaseDateByOneDecade()
    {
        return IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(clsDate &Date,short NumOfDecades)
    {
    for (int i = 1;i<=NumOfDecades;i++)
    {
        Date = IncreaseDateByOneDecade(Date);
    }
    return Date;
    }
    clsDate IncreaseDateByXDecades(short NumOfDecades)
    {
        return IncreaseDateByXDecades(*this,NumOfDecades);
    }

    static clsDate IncreaseDateByXDecadesFaster(clsDate &Date,short NumOfDecades)
    {
    Date.Year += (NumOfDecades*10);
    return Date;
    }
    clsDate IncreaseDateByXDecadesFaster(short NumOfDecedaes)
    {
        return IncreaseDateByXDecadesFaster(*this,NumOfDecedaes);
    }

    static clsDate IncreaseDateByOneCentury(clsDate &Date)
    {
    Date.Year += 100;
    return Date;
    }
    clsDate IncreaseDateByOneCentury()
    {
        return IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate &Date)
    {
    Date.Year += 1000;
    return Date;
    }  
    clsDate IncreaseDateByOneMillennium()

    {
        return IncreaseDateByOneMillennium(*this);
    }

    static bool IsFirstDayInMonth(clsDate &Date)
    {
    return Date.Day == 1;
    }
    bool IsFirstDayInMonth()
    {
        return IsFirstDayInMonth(*this);
    }

    static bool IsFirstMonthInYear(clsDate &Date)
    {
    return Date.Month == 1;
    }
    bool IsFirstMonthInYear()
    {
        return IsFirstMonthInYear(*this);
    }

    static clsDate SubtractDateByOneDay(clsDate &Date)
    {
    if (IsFirstDayInMonth(Date)) // 1/12/2023
    {
        if (IsFirstMonthInYear(Date))
        {
            Date.Month = 12;
            Date.Year--;
            Date.Day = NumberOfDaysInAMonth(Date.Year,Date.Month);
        }
        else
        {
            Date.Month--;
            Date.Day = NumberOfDaysInAMonth(Date.Year,Date.Month);
        }
    }
    else
    {
        Date.Day--;
    }

    return Date;
    }
    clsDate SubtractDateByOneDay()
    {
        return SubtractDateByOneDay(*this);
    }

    static clsDate SubtractDateByXDays(clsDate &Date,short NumOfDays)
    {
    for (int i = 1;i<=NumOfDays;i++)
        Date = SubtractDateByOneDay(Date);

    return Date;
    }
    clsDate SubtractDateByXDays(short NumOfDays)
    {
        return SubtractDateByXDays(*this,NumOfDays);
    }
    
    static clsDate SubtractDateByOneWeek(clsDate &Date)
    {
    for (short i = 1;i<=7;i++)
    {
        Date = SubtractDateByOneDay(Date);
    }

    return Date;
    }
    clsDate SubtractDateByOneWeek()
    {
        return SubtractDateByOneWeek(*this);
    }

    static clsDate SubtractDateByXWeeks(clsDate &Date,short NumOfWeeks)
    {
    for (int i = 1;i<=NumOfWeeks;i++)
        Date = SubtractDateByOneWeek(Date);

    return Date;
    }
    clsDate SubtractDateByXWeeks(short NumOfWeeks)
    {
        return SubtractDateByXWeeks(*this,NumOfWeeks);
    }

    static clsDate SubtractDateByMonth(clsDate &Date)
    {

    if (IsFirstMonthInYear(Date))
    {
        Date.Month = 12;
        Date.Year--;
    }
    else
    {
        Date.Month--;
    }
    //last check day in date should not exceed max days in the current month
    // example if date is 31/3/2022 decreasing one month should not be 31/2/2022,
    //it should// be 28/2/2022
    short NumOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Year,Date.Month);

    if (Date.Day>NumOfDaysInCurrentMonth)
    {
        Date.Day = NumOfDaysInCurrentMonth;
    }

    return Date;

    }
    clsDate SubtractDateByMonth()
    {
        return SubtractDateByMonth(*this);
    }

    static clsDate SubtractDateByXMonths(clsDate &Date,short NumOfMonths)
    {
    for (int i = 1;i<=NumOfMonths;i++)
    {
        Date = SubtractDateByMonth(Date);
    }
    return Date;
    }
    clsDate SubtractDateByXMonths(short NumOfMonths)
    {
        return SubtractDateByXMonths(*this,NumOfMonths);
    }

    static clsDate SubtractDateByOneYear(clsDate &Date)
    {
    Date.Year--;
    return Date;
    }
    clsDate SubtractDateByOneYear()
    {
        return SubtractDateByOneYear(*this);
    }

    static clsDate SubtractDateByXYears(clsDate &Date,short NumOfYears)
    {
    for (int i = 1;i<=NumOfYears;i++)
    {
        Date = SubtractDateByOneYear(Date);
    }

    return Date;
    }
    clsDate SubtractDateByXYears(short NumOfYears)
    {
        return SubtractDateByXYears(*this,NumOfYears);
    }

    static clsDate SubtractDateByXYearsFaster(clsDate &Date,short NumOfYears)
    {
    Date.Year -= NumOfYears;
    return Date;
    }
    clsDate SubtractDateByXYearsFaster(short NumOfYears)
    {
        return SubtractDateByXYearsFaster(*this,NumOfYears);
    }

    static clsDate SubtractDateByOneDecade(clsDate &Date)
    {
    Date = SubtractDateByXYears(Date,10);
    return Date;
    }
    clsDate SubtractDateByOneDecade()
    {
        return SubtractDateByOneDecade(*this);
    }

    static clsDate SubtractDateByXDecades(clsDate &Date,short NumOfDecades)
    {   
    for (int i = 1;i<=NumOfDecades;i++)
    {
        Date = SubtractDateByOneDecade(Date);
    }
    return Date;
    }
    clsDate SubtractDateByXDecades(short NumOfDecades)
    {
        return SubtractDateByXDecades(*this,NumOfDecades);
    }

	static clsDate SubtractDateByXDecadesFaster(clsDate &Date,short NumOfDecades)
	{
	    Date.Year -= (NumOfDecades*10);
	    return Date;
	}
    clsDate SubtractDateByXDecadesFaster(short NumOfDecades)
    {
        return SubtractDateByXDecadesFaster(*this,NumOfDecades);
    }

    static clsDate SubtractDateByOneCentury(clsDate &Date)
    {
        Date.Year -= 100;
        return Date;
    }
    clsDate SubtractDateByOneCentury()
    {
        return SubtractDateByOneCentury(*this);
    }

    static clsDate SubtractDateByOneMillennium(clsDate &Date)
    {
    Date.Year -= 1000;
    return Date;
    }       
    clsDate SubtractDateByOneMillennium()
    {
        return SubtractDateByOneMillennium(*this);
    }

    // No Need For Non-Static function for the object cuz it does not depend on any data from it.
    static int CalculateMyAgeInDays(clsDate Date1)
    {   
    int AgeInDays = 0;

    clsDate CurrentDate;
    CurrentDate.Day = 8;
    CurrentDate.Month = 12;
    CurrentDate.Year = 2025;

    while (IsDate1BeforeDate2(Date1,CurrentDate))
    {
        Date1 = IncreaseDateByOneDay(Date1);
        AgeInDays++;
    }

    return AgeInDays;
    }

    static short GetDayOrder(short Year,short Month,short Day)
    {
    short a = (14-Month)/12;
    short y = Year - a;
    short m = Month + (12*a) - 2;

    short d = (Day + y + (y/4) - (y/100) + (y/400) + (31*m)/12) % 7;

    return d;
    } 
    short GetDayOrder()
    {
        return GetDayOrder(this->Year,this->Month,this->Day);
    }

    static bool IsEndOfWeek(clsDate Date)
    {
    return GetDayOrder(Date.Year,Date.Month,Date.Day) == 6;
    }
    bool IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
    short DayIndex = GetDayOrder(Date.Year,Date.Month,Date.Day);
    return DayIndex == 5 || DayIndex==6;
    }
    bool IsWeekEnd()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
    //Weekends are Sun,Mon,Tue,Wed and Thur/* short DayIndex = DayOfWeekOrder(Date);   
    //return  (DayIndex >= 5 && DayIndex <= 4);   
    ///shorter method is to invert the IsWeekEnd: this will save updating code.
    return !IsWeekEnd(Date); 
    }
    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }
 
    static short DaysUntilTheEndOfWeek(clsDate Date) 
    { 
    return 6 - GetDayOrder(Date.Year,Date.Month,Date.Day);
    } 
    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short GetDiffInDays(clsDate Date1,clsDate Date2, bool IncludedLastDay = false)
    {
    short Counter = 0;

    while (IsDate1BeforeDate2(Date1,Date2))
    {
        Counter++;
        Date1 = IncreaseDateByOneDay(Date1);
    }

   return IncludedLastDay? (++Counter) : Counter;
    }

    static short DaysUntilTheEndOfMonth(clsDate Date)
    {   

    clsDate EndOfMonthDate;
    EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Year,Date.Month);
    EndOfMonthDate.Month = Date.Month;
    EndOfMonthDate.Year = Date.Year;

    return GetDiffInDays(Date,EndOfMonthDate,true);
    }

    static short DaysUntilTheEndOfYear(clsDate Date)
    {
    clsDate EndOfYearDate;
    EndOfYearDate.Day = 31;
    EndOfYearDate.Month =12;
    EndOfYearDate.Year = Date.Year;
    return GetDiffInDays(Date,EndOfYearDate,true);
    }

    static short CountVacationDays(clsDate StartVacation,clsDate EndVacation)
    {
    short CountVacationDays = 0;

    while(IsDate1BeforeDate2(StartVacation,EndVacation))
    {

        if(IsBusinessDay(StartVacation))
         CountVacationDays++;

         StartVacation = IncreaseDateByOneDay(StartVacation);       
    }

    return CountVacationDays;
    }

    static short CountBusinessDays(clsDate DateFrom,clsDate DateTo)
    {
        short CountBusinessDays = 0;

    while(IsDate1BeforeDate2(DateFrom ,DateTo))
    {

        if(IsBusinessDay(DateFrom ))
         CountBusinessDays++;

         DateFrom = IncreaseDateByOneDay(DateFrom );       
    }

    return CountBusinessDays;
    
    }

    enum enCompare {Before = -1,Equal,After};

    static enCompare CompareDates(clsDate Date1,clsDate Date2)
    {
    if(IsDate1BeforeDate2(Date1,Date2))
    {
        return Before;
    }
    if (IsDate1AfterDate2(Date1,Date2))
    {
        return After;
    }
    return Equal;

    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom,short VacationDays)
    {
    short WeekendCounter = 0;

    //in case the date is weekend, keep adding one day util you reach business day.
    //we get rid of all weekends before the first business day.

    while(IsWeekEnd(DateFrom))
    {
        DateFrom = IncreaseDateByOneDay(DateFrom);
    }

    // here the start is from a business day.
    //here we increase the vacation dates to add all weekends to it.

    for(short i =1;i<=VacationDays + WeekendCounter;i++)
    {
        if(IsWeekEnd(DateFrom))
        {
            WeekendCounter++;
        }

        DateFrom = IncreaseDateByOneDay(DateFrom);
    }

    while(IsWeekEnd(DateFrom))
    {
        DateFrom = IncreaseDateByOneDay(DateFrom);
    }

    return DateFrom;
    }

    static short NumOfDaysFromBeginningOfTheYear(short Day,short Month,short Year)
    {
    short CountDays = 0;

    for (int CurrentMonth = 1;CurrentMonth<Month;CurrentMonth++)
    {
        CountDays += NumberOfDaysInAMonth(CurrentMonth,Year);
    }

    CountDays += Day;

    return CountDays;
    }

    short NumOfDaysFromBeginningOfTheYear()
    {
        return NumOfDaysFromBeginningOfTheYear(this->Day,this->Month,this->Year);
    }

    static clsDate GetDateFromDayOrder(short DateOrderInYear,short Year)
    {
    clsDate Date;
    Date.Year = Year;
    Date.Month = 1;

    short RemainingDays = DateOrderInYear;

    while (true)
    {
        if (RemainingDays>NumberOfDaysInAMonth(Date.Month,Year))
        {
            RemainingDays -= NumberOfDaysInAMonth(Date.Month,Year);
            Date.Month++;
        }
        else
        {
            Date.Day = RemainingDays;
            break;
        }
    }
    return Date;
    }   

    static string DayShortName(short DayOfWeekOrder)
    {
        string Arr[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

        return Arr[DayOfWeekOrder];  
    }
    static string DayShortName(short Day,short Year,short Month)
    {
    string Arr[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    return (Arr[GetDayOrder(Year,Month,Day)]);
    }
    string DayShortName()
    {
        return DayShortName(this->Day,this->Month,this->Year);
    }

    

};

