#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurreny.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{

    private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n________________________";
        cout << "\nCountry   : " << Currency.GetCountry();
        cout << "\nCode      : " << Currency.GetCountryCode();
        cout << "\nName      : " << Currency.GetCurrencyName();
        cout << "\nRate(1$)  : " << Currency.GetRate();
        cout << "\n________________________\n";
    }

    public:

    static void ShowCurrencyCalculatorScreen()
    {
        _DrawScreenHeader("\tCurrency Calculator Screen");
        
        

    }


};