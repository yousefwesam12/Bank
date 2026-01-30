#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurreny.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyScreen : protected clsScreen
{

    private:
    static void _PrintCurrency(clsCurrency &Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n________________________";
        cout << "\nCountry   : " << Currency.GetCountry();
        cout << "\nCode      : " << Currency.GetCountryCode();
        cout << "\nName      : " << Currency.GetCurrencyName();
        cout << "\nRate(1$)  : " << Currency.GetRate();
        cout << "\n________________________\n";
    }
    static string _ReadCurrencyCode()
    {
        string CurrencyCode = "";
        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

       return CurrencyCode;
    }
    
    public:

    static void ShowUpdateCurrencyRateScreen()
    {
        _DrawScreenHeader("\t Update Currency Screen");
        
        string CurrencyCode = _ReadCurrencyCode();

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        if(Currency.IsEmpty())
        {
            cout << "\n" << "No Currency Found with this code.. the update is failed ):\n";
            return;
        }
        
        _PrintCurrency(Currency);
        char Answer = 'n';
        cout << "\n" << "Are you sure you want to update the rate of this currency? y/n? ";
        cin >> Answer;

        if(tolower(Answer) != 'y')
        {
            return;
        }

        cout << "\nUpdate Currency Rate:\n";
        cout << "--------------------------\n";

        float NewRate = 0;
        cout << "Enter New Rate: ";
        NewRate = clsInputValidate::ReadNumber<double>();

        Currency.UpdateRate(NewRate);

        cout << "\n" << "Currency Rate Updated Successfully :-)";

        _PrintCurrency(Currency);


    }


};