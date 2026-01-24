#pragma once
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include <iostream>
#include "clsScreen.h"

class clsFindUserScreen : protected clsScreen
{

    static void _PrintUser(clsBankUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.GetFullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUsername();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }
 

    public:
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\tFind User Screen");

        string Username = "";
        cout << "\n" << "Please Enter User Username: ";
        Username = clsInputValidate::ReadString();

        while(!clsBankUser::IsUserExist(Username))
        {
            cout << "Username Is Not Found, Enter another one : ";
            Username = clsInputValidate::ReadString();
        }

             
        clsBankUser User = clsBankUser::Find(Username);

        if(!User.IsEmpty())
        {
            cout << "\n" << "User Found :-)\n";
        }
        else
        {
            cout << "\n" << "User was not found :-(\n";
        }

        _PrintUser(User);
    }
};