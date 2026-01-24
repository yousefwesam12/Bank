#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersScreen : protected clsScreen
{

    private:
    enum _enManageUsersChoices
    {
        eListUser = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };

    static void _ClearScreen()
    {
        system("clear");
    }
    
    static void _GoBackToUsersMenue()
    {
        cout << "Press any key to go back to main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        _ClearScreen();
        ShowManageUsersScreen();
    }
    
    static void _PerformUserMenuScreen(_enManageUsersChoices ManageUserChoice)
    {
        switch (ManageUserChoice)
        {
        case eListUser:
            _ClearScreen();
            _ShowListUsersScreen();
            _GoBackToUsersMenue();
            break;

        case eAddNewUser:
            _ClearScreen();
            _ShowAddNewUserScreen();
            _GoBackToUsersMenue();
            break;

        case eDeleteUser:
            _ClearScreen();
            _ShowDeleteUserScreen();
            _GoBackToUsersMenue();
            break;

        case eUpdateUser:
            _ClearScreen();
            _ShowUpdateUserScreen();
            _GoBackToUsersMenue();
            break;

        case eFindUser:
            _ClearScreen();
            _ShowFindUserScreen();
            _GoBackToUsersMenue();
            break;

        case eMainMenue:
            break;
            // The Compiler will handle it.
        }
    }

    static short _ReadUsersMenuChoice()
    {
        short Choice = 0;
        cout << setw(37) << left << "" << "Choose What Do You want to do? [1 to 6]? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1,6);
        return Choice;
    }

    static void _ShowListUsersScreen()
    {
        //cout << "\n" << "List Users screen will be here..\n";
        clsListUsersScreen::ShowListUsersScreen();
    }
    
    static void _ShowAddNewUserScreen()
    {
        //cout << "\n" << "Add New User screen will be here..\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    
    static void _ShowDeleteUserScreen()
    {
        //cout << "\n" << "Delete User screen will be here..\n";  
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    
    static void _ShowUpdateUserScreen()
    {
        //cout << "\n" << "Update User screen will be here..\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    
    static void _ShowFindUserScreen()
    {
       // cout << "\n" << "Find User screen will be here..\n";
       clsFindUserScreen::ShowFindUserScreen();
    }
    
    public:
    static void ShowManageUsersScreen()
    {
        _DrawScreenHeader("\t Manage Users Screen");

            cout << setw(37)  << left  << "" << "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t\t Manage Users  Menue\n";
            cout << setw(37) << left << ""  <<  "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t[1] List Users.\n";
            cout << setw(37) << left << ""  <<  "\t[2] Add New User.\n";
            cout << setw(37) << left << ""  <<  "\t[3] Delete User.\n";
            cout << setw(37) << left << ""  <<  "\t[4] Update User.\n";
            cout << setw(37) << left << ""  <<  "\t[5] Find User.\n";
            cout << setw(37) << left << ""  <<  "\t[6] Main Menue.\n";
            cout << setw(37) << left << "" <<   "===========================================\n";
            _PerformUserMenuScreen(_enManageUsersChoices(_ReadUsersMenuChoice()));
    }

};

