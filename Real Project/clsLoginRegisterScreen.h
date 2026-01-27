#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsBankUser.h"

class clsLoginRegisterScreen : protected clsScreen
{


    private:
    static void PrintLoginRegisterRecord(clsBankUser::stLoginRegisterInfo LoginRegisterInfo)
    {   
        
        cout << "| " << setw(30) << left << LoginRegisterInfo.DateAndTime;
        cout << "| " << setw(20) << left << LoginRegisterInfo.Username;
        cout << "| " << setw(20) << left << LoginRegisterInfo.Password;
        cout << "| " << setw(20) << left << LoginRegisterInfo.Permissions;
    }

    public:
    static void ShowLoginRegisterScreen()
    {
        if (!CurrentUser.HasAccessToThisPermission(clsBankUser::pLogRegister))
        {
            ShowAccessDeniedMessage();
            return;
        }
        vector <clsBankUser::stLoginRegisterInfo> vLoginInfo = clsBankUser::GetLoginRegisterInfo();
        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(vLoginInfo.size()) + ") Record(s).";

        _DrawScreenHeader(Title,SubTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginInfo.size() == 0)
            cout << "\t\t\t\tNo Login Register Info Available In the System!";

        else
            for (clsBankUser::stLoginRegisterInfo &LoginInfo : vLoginInfo)
            {

                PrintLoginRegisterRecord(LoginInfo);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};