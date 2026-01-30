#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "clsString.h"
#include <vector>

using namespace std;


class clsCurrency
{

    private:
    enum enMode {EmptyMode = 0,UpdateMode = 1};
    string _Country;
    string _CountryCode;
    string _CurrencyName;
    double _Rate;
    enMode _Mode;


    static clsCurrency _ConvertLineToCurrencyObject(string stLine,string Seperator = "#//#")
    {
        // United States of America#//#USD#//#US Dollar#//#1.000000
        vector <string> vLine = clsString::Split(stLine,Seperator);
        return clsCurrency(UpdateMode,vLine[0],vLine[1],vLine[2],stod(vLine[3]));
    }

    static vector <clsCurrency> _LoadCurrnecyListFromTheFile()
    {

        vector <clsCurrency> vCurrencyList;
        fstream MyFile;
        MyFile.open("Currencies.txt",ios::in);

        if(MyFile.is_open())
        {

            string Line;
            
            while (getline(MyFile,Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                vCurrencyList.push_back(Currency);
            }
            
            MyFile.close();
        }

        return vCurrencyList;


    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency,string Seperator = "#//#")
    {
        string Line = "";
        Line += Currency.GetCountry() + Seperator;
        Line += Currency.GetCountryCode() + Seperator;
        Line += Currency.GetCurrencyName() + Seperator;
        Line += to_string(Currency.GetRate());
        return Line;
    }

    static clsCurrency GetEmptyCurrencyObject()
    {
        return clsCurrency(EmptyMode,"","","",0);
    }

    void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies)
    {

        fstream MyFile;
        MyFile.open("Currencies.txt",ios::out);

        if(MyFile.is_open())
        {

            for(clsCurrency &C : vCurrencies)
            {
                string stLine = _ConvertCurrencyObjectToLine(C);

                MyFile << stLine << endl;
            }


            MyFile.close();
        }


    }

    void _Update()
    {
        vector <clsCurrency> vCurrencies = _LoadCurrnecyListFromTheFile();

        for(clsCurrency &Currency : vCurrencies)
        {
            if(Currency.GetCountryCode() == GetCountryCode())
            {
                Currency = *this;
                break;
            }
        }

        _SaveCurrencyDataToFile(vCurrencies);

    }

    public:
    clsCurrency(enMode Mode,string Country,string CountryCode,string CurrencyName,double Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CountryCode = CountryCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }
    
    string GetCountry()
    {
        return _Country;
    }
    
    string GetCountryCode()
    {
        return _CountryCode;
    }

    string GetCurrencyName()
    {
        return _CurrencyName;
    }

    double GetRate()
    {
        return _Rate;
    }

    // Find By : [1] Code or [2] Country ? 
    static clsCurrency FindByCode(string CountryCode)
    {
        CountryCode = clsString::UpperAllString(CountryCode);
        fstream MyFile;

        MyFile.open("Currencies.txt",ios::in);

        if(MyFile.is_open())
        {

            string Line = "";

            while(getline(MyFile,Line))
            {

                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                if(Currency.GetCountryCode() == CountryCode)
                {
                    MyFile.close();
                    return Currency;
                }
                
            }

            MyFile.close();
        }

        return GetEmptyCurrencyObject();
        
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);
        fstream MyFile;

        MyFile.open("Currencies.txt",ios::in);

        if(MyFile.is_open())
        {

            string Line = "";

            while(getline(MyFile,Line))
            {

                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                if(clsString::UpperAllString(Currency.GetCountry()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
                
            }

            MyFile.close();
        }
        return GetEmptyCurrencyObject();
    }

    bool IsEmpty()
    {
        return _Mode == EmptyMode;
    }
     
    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C = FindByCode(CurrencyCode);

        return !(C.IsEmpty());
    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrnecyListFromTheFile();
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }
    
    float ConvertToUSD(float Amount)
    {
       return (Amount /GetRate());
    }

    float ConvertToOtherCurrnecy(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if(Currency2.GetCountryCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD*Currency2.GetRate());
    }
};