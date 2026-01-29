#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurreny.h"
using namespace std;

class clsCurrencyListScreen : protected clsScreen
{
    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
        cout << "| " << setw(8) << left << Currency.GetCountryCode();
        cout << "| " << setw(45) << left << Currency.GetCurrencyName();
        cout << "| " << setw(10) << left << Currency.GetRate();
    }

    public:
    static void ShowCurrencyListScreen()
    {
        vector <clsCurrency> vCurrencyList = clsCurrency::GetCurrenciesList();

        string Title = "\t Currencies List Screen";
        string SubTitle = "\t   (" + to_string(vCurrencyList.size()) + ") Currency(s).";

        _DrawScreenHeader(Title,SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if(vCurrencyList.size() == 0)
        {
            cout << "\t\t\t\tNo Currency List Available In the System!";
        }
        else
        {
            for(clsCurrency Currency : vCurrencyList)
            {
                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};