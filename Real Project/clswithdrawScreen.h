#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
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
    

    public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t Withdraw Screen");

        string AccountNumber = "";
        cout << "\n" << "Please Enter an account number: ";
        AccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << "There is no client with [" << AccountNumber << "], Enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "Please Enter withdraw amount? ";
        Amount = clsInputValidate::ReadDoubleNumber();

        char answer = 'n';
        cout << "\n" << "Are you sure you want to perform this transaction? Y/N? ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')    
        {
            if(Client.Withdraw(Amount))
            {
                cout << "\n" << "Account Withdrawed Successfully.\n";
                cout << "\n" << "New Balance is " << Client.GetAccountBalance() << endl;

            }
            else
            {
                cout << "\n" << "The Amount Exceeds, you can withdraw up to : " << Client.GetAccountBalance() << endl;
                cout << "\n" << "Your Balance is " << Client.GetAccountBalance() << endl;

            }
        } 
        else
        {
            cout << "\n" << "The operation is cancelled.\n";
        }

    }

};