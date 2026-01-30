#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRate.h"

using namespace std;

class clsMainCurrencyScreen : clsScreen
{
    enum _enCurrencyScreenChoices
    {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCurrencyCalculator = 4, eMainMenue   = 5
    };

    static void _ClearScreen()
    {
        system("clear");
    }
    
    static void _GoBackToCurrnecyMenue()
    {
        cout << "Press any key to go back to currency main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        _ClearScreen();
        ShowMainCurrencyScreen();
    
    }
    
    static short _ReadMainCurrnectyScreenChoice()
    {
        short Choice = 0;
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1,5);
        return Choice;
    }

    static void _ShowListCurrenciesScreen()
    {
        //cout << "\n" << "List Currencies Screen will be here..\n";
        clsCurrencyListScreen::ShowCurrencyListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "\n" << "Find Currency Screen will be here..\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\n" << "Update Rate Screen will be here..\n";
        clsUpdateCurrencyScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        cout << "\n" << "Currency Calculator Screen will be here..\n";
    }
    
    static void _PerformCurrencyScreenOption(_enCurrencyScreenChoices CurrencyChoice)
    {
        switch(CurrencyChoice)
        {
            case eListCurrencies:
            _ClearScreen();
            _ShowListCurrenciesScreen();
            _GoBackToCurrnecyMenue();
            break;

            case eFindCurrency:
            _ClearScreen();
            _ShowFindCurrencyScreen();
            _GoBackToCurrnecyMenue();
            break;

            case eUpdateRate:
            _ClearScreen();
            _ShowUpdateRateScreen();
            _GoBackToCurrnecyMenue();
            break;

            case eCurrencyCalculator:
            _ClearScreen();
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrnecyMenue();
            break;

            case eMainMenue:
            // The compiler will handle it.
        }
    }

    public:
    static void ShowMainCurrencyScreen()    
    {
        
        _ClearScreen();
            _DrawScreenHeader("\t Currency Exchange Main Screen");
            cout << setw(37)  << left  << "" << "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t\tCurrency Exchange Menue\n";
            cout << setw(37) << left << ""  <<  "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t[1] List Currencies.\n";
            cout << setw(37) << left << ""  <<  "\t[2] Find Currency.\n";
            cout << setw(37) << left << ""  <<  "\t[3] Update Rate.\n";
            cout << setw(37) << left << ""  <<  "\t[4] Currency Calculator.\n";
            cout << setw(37) << left << ""  <<  "\t[5] Main Menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            _PerformCurrencyScreenOption(_enCurrencyScreenChoices(_ReadMainCurrnectyScreenChoice()));

    }

};