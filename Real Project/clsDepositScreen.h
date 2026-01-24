#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"


class clsDepositScreen : protected clsScreen
{

    private:
    static void _PrintClient(clsBankClient &Client)
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
    };
    
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\n" << "\tEnter Account Number? ";
        cin >> AccountNumber;

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << "Invalid Account Number, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }


    public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t Deposit Screen");
        string AccountNumber = _ReadAccountNumber();

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double DepositValue = 0;

        cout << "Please enter deposit amount? ";
        DepositValue = clsInputValidate::ReadDoubleNumber();

        char answer = 'n';
        cout << "\n" << "Are you sure you want to perform this transaction? Y/N? ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')    
        {
            Client.Deposit(DepositValue);
            cout << "\n" << "Account Deposited Successfully.\n";
            cout << "\n" << "New Balance is " << Client.GetAccountBalance() << endl;
        }    

    }

};