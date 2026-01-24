#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
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
    static void _ShowDeleteClientScreen()
    {
        _DrawScreenHeader("\t Delete Client Screen");

        string AccountNumber = "";
        cout << "Please Enter Account Number : ";
        cin >> AccountNumber;

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << "This Account Number is not exist, enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Answer = 'y';

        cout << "\n" << "Are you sure you want to delete this client? [y/n]? ";
        cin >> Answer;

        if(Answer == 'y' || Answer == 'Y')
        {
            if(Client.Delete())
            {
                cout << "\n" << "Client Deleted Successfuly.\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\n" << "Error, this client was not deleted.\n";
            }
        }

    }
};