#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsAddNewClientScreen : protected clsScreen
{

    private:
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
    static void ShowAddNewClientScreen()
    {

        _DrawScreenHeader("\t Add New Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {

        case clsBankClient::enSaveResults::enSaveSucceeded:
        {
        cout << "\nAccount Added Successfully :-)\n";
        _PrintClient(NewClient);
        break;
        }

        case clsBankClient::enSaveResults::enSaveFailedEmptyObject:
        {
        cout << "\nError account was not saved because it's Empty";
        break;
        }
        case clsBankClient::enSaveResults::SvFailedAccountNumberExists:
        {
        cout <<"\nError account number is used.";
        break;
        }
        }

    }

}; 