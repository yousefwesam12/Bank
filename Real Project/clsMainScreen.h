#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListClientsScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsAddNewClient.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

    private:
    enum _enMainScreenChoices
    {
        eShowClientList = 1, eAddNewClient = 2, eDeleteCLient = 3,
        eUpdateClient   = 4, eFindClient   = 5, eTransactions = 6,
        eManageUsers    = 7, eLogout       = 8
    };
    
    static short _ReadMainScreenChoice()
    {
        short Choice = 0;
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1,8);
        return Choice;
    }
    
    static void _ClearScreen()
    {
        system("clear");
    }
    
    static void _GoBackToMainMenue()
    {
        cout << "Press any key to go back to main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        _ClearScreen();
        ShowMainMenue();
    }
    
    static void _PerformMainMenueOption(_enMainScreenChoices MainScreenChoice)
    {
        switch(MainScreenChoice)
        {
            case eShowClientList:
            _ClearScreen();
            _ShowListClientsScreen();
            _GoBackToMainMenue();
            break;

            case eAddNewClient:
            _ClearScreen();
            _ShowAddNewClientScreen();
            _GoBackToMainMenue();
            break;

            case eDeleteCLient:
            _ClearScreen();
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

            case eUpdateClient:
            _ClearScreen();
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

            case eFindClient:
            _ClearScreen();
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

            case eTransactions:
            _ClearScreen();
            _ShowTransactionsScreen();
            _GoBackToMainMenue();
            break;

            case eManageUsers:
            _ClearScreen();
            _ShowManageUsersScreen();
            _GoBackToMainMenue();
            break;

            case eLogout:
            _ClearScreen();
            _ShowLogoutScreen();
            _GoBackToMainMenue();
            break;

            default:
            break;
        }
    }
    
    static void _ShowListClientsScreen()
    {
        //cout << "\n" << "List Client Screen Will be here..\n";
        clsListClientsScreen::ShowClientsList();
    }
    
    static void _ShowAddNewClientScreen()
    {
        //cout << "\n" << "Add New Client Screen Will be here..\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }
    
    static void _ShowDeleteClientScreen()
    {
        //cout << "\n" << "Delete Client Screen Will be here..\n";
        clsDeleteClientScreen::_ShowDeleteClientScreen();
    }
    
    static void _ShowUpdateClientScreen()
    {
         //cout << "\n" << "Update Client Screen Will be here..\n";
         clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    
    static void _ShowFindClientScreen()
    {
        //cout << "\n" << "Find Client Screen Will be here..\n";
        clsFindClientScreen::ShowFindClientScreen();
    }
    
    static void _ShowTransactionsScreen()
    {
        //cout << "\n" << "Transactions Screen Will be here..\n";
        clsTransactionsScreen::ShowTransactionsScreen();
    }
    
    static void _ShowManageUsersScreen()
    {
        //cout << "\n" << "Manage Users Screen Will be here..\n";
        clsManageUsersScreen::ShowManageUsersScreen();
    }
    
    static void _ShowLogoutScreen()
    {
        cout << "\n" << "Logout Screen Will be here..\n";
    }


    public:
    static void ShowMainMenue()
    {
            clsScreen::_DrawScreenHeader("\t\tMain Screen");

            cout << setw(37)  << left  << "" << "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t\t\tMain Menue\n";
            cout << setw(37) << left << ""  <<  "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t[1] Show Client List.\n";
            cout << setw(37) << left << ""  <<  "\t[2] Add New Client.\n";
            cout << setw(37) << left << ""  <<  "\t[3] Delete Client.\n";
            cout << setw(37) << left << ""  <<  "\t[4] Update Client.\n";
            cout << setw(37) << left << ""  <<  "\t[5] Find Client.\n";
            cout << setw(37) << left << ""  <<  "\t[6] Transactions.\n";
            cout << setw(37) << left << ""  <<  "\t[7] Manage Users.\n";
            cout << setw(37) << left << ""  <<  "\t[8] Exit.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            _PerformMainMenueOption(_enMainScreenChoices(_ReadMainScreenChoice()));
    }


};