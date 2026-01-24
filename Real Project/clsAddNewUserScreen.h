#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
    private:
    
    static int  _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char answer = 'n';

        cout << "\n" << "Enter Permissions: ";
        cout << "\n" << "Do you want to give full access? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions = -1;
            return Permissions;
        }

        cout << "\n" << "Do you want to give access to : ";


        cout << "\n" << "Show Client List? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pListClients;
        }

        cout << "\n" << "Add New Client? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pAddNewClient;
        }

        cout << "\n" << "Delete Client? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pDeleteClient;
        }
        cout << "\n" << "Update Client? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pUpdateClient;
        }
        cout << "\n" << "Find Client? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pFindClient;
        }
        cout << "\n" << "Transactions? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pTransactions;
        }
        cout << "\n" << "Manage Users? y/n? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            Permissions += clsBankUser::pManageUsers;
        }

        return Permissions;

    }

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
    
    static void _ReadUserInfo(clsBankUser &User)
    {
     
        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.SetPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permissions: ";
        User.SetPermission(_ReadPermissionsToSet());

    }

    public:
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\tAdd New User Screen");

        string Username = "";
        cout << "\n" << "Please Enter UserName: ";
        Username = clsInputValidate::ReadString();

        while(clsBankUser::IsUserExist(Username))
        {
            cout << "UserName Is Already Used, Choose another one : ";
            Username = clsInputValidate::ReadString();
        }

        clsBankUser User = clsBankUser::GetAddNewUserObject(Username);
        _ReadUserInfo(User);

        clsBankUser::enSaveResults SaveResults;

        SaveResults = User.Save();

        switch(SaveResults)
        {
            case clsBankUser::enSaveResults::svSucceeded:
                 cout << "\n" << "User Added Successfully (:-.\n";
                _PrintUser(User);
                break;
            
            case clsBankUser::enSaveResults::svFailedEmptyObject:
                cout << "\n" << "Error, user was not saved because it's empty.\n";
                break;

            case clsBankUser::enSaveResults::svFailedUserExists:
                cout << "\n" << "Error, user was not saved because it's exist.\n";
                break;
        }

    }

};