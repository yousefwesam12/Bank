#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurreny.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{

    private:

    static int _ReadFindByChoice()
    {
        int Choice = 0;
        cout << "\nFind By: [1] Code or [2] Country ? ";
        Choice = clsInputValidate::ReadNumberBetween<int>(1,2);
        return Choice;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n________________________";
        cout << "\nCountry   : " << Currency.GetCountry();
        cout << "\nCode      : " << Currency.GetCountryCode();
        cout << "\nName      : " << Currency.GetCurrencyName();
        cout << "\nRate(1$)  : " << Currency.GetRate();
        cout << "\n________________________\n";
    }

    static string _ReadCountryName()
    {
        string CountryName = "";
        cout << "\nPlease Enter Country Name: ";
        CountryName = clsInputValidate::ReadString();

       return CountryName;
    }

    static string _ReadCountryCode()
    {
        string CountryCode = "";
        cout << "\nPlease Enter Country Code: ";
        CountryCode = clsInputValidate::ReadString();

       return CountryCode;
    }
    
    public:

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t Find Currency Screen");
        int Choice = _ReadFindByChoice();

        clsCurrency Currency = clsCurrency::FindByCode("0");

        if(Choice == 1)
        {
            string CountryCode = _ReadCountryCode();
            Currency = clsCurrency::FindByCode(CountryCode);
        }
        else if(Choice == 2)
        {
            string CountryName = _ReadCountryName();
            Currency = clsCurrency::FindByCountry(CountryName);
        }

        if(Currency.IsEmpty())
        {
            cout << "\n" << "No Currency exists with this data ):-\n";
        }
        else
        {
            cout << "\n" << "Currency Found (:\n";
            _PrintCurrency(Currency);
        }



    }


};