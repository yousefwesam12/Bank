#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{

    private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

    public:
    static void ShowFindClientScreen()
    {
         if(!CurrentUser.HasAccessToThisPermission(clsBankUser::pFindClient))
        {
            ShowAccessDeniedMessage();
            return;
        }
        _DrawScreenHeader("\t Find Client Screen");

        string AccountNumber = "";
        cout << "\n" << "Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if(!Client.IsEmpty())
        {
            cout << "\n" << "Client Found :-)\n";
        }
        else
        {
            cout << "\n" << "Client Was Not Found ):\n";
        }

        _PrintClient(Client);


    }


};