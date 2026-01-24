#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
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
     static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\n" << "Please Enter First Name : ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\n" << "Please Enter Last Name : ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\n" << "Please Enter Email : ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\n" << "Please Enter Phone : ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\n" << "Please Enter Pin Code : ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\n" << "Please Enter Account Balance : ";
        Client.SetAccountBalance(clsInputValidate::ReadDoubleNumber());
    }
    


    public:
    static void ShowUpdateClientScreen()
    {
        _DrawScreenHeader("\t Update Client Screen");

        string AccountNumber = "";
        cout << "\n" << "Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << "The Account Number is not found, enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        
        char Answer = 'Y';
        cout << "Do you want to update this client? [Y/N]? ";
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            _ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResults;

            SaveResults = Client.Save();

            switch(SaveResults)
            {
                case clsBankClient::enSaveSucceeded:
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client);
                break;

                case clsBankClient::enSaveFailedEmptyObject:
                {
                cout << "\nError account was not saved because it's Empty";
                break;
                }

            }

        }

    }

};