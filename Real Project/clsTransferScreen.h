#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
    static string _ReadAccountNumber(string Message)
    {
        string AccountNumber = "";
        cout << Message;
        AccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\n" << "There is no client with this account number, enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static void _PrintClient(clsBankClient &Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    };

    public:
    static void ShowTransferScreen()
    {
        string AccountNumberFrom = _ReadAccountNumber("\nPlease Enter Account Number To Transfer From: ");
        clsBankClient ClientFrom = clsBankClient::Find(AccountNumberFrom);
        _PrintClient(ClientFrom);

        string AccountNumberTo = _ReadAccountNumber("\nPlease Enter Account Number To Transfer To: ");
        clsBankClient ClientTo = clsBankClient::Find(AccountNumberTo);
        _PrintClient(ClientTo);

        double TransferAmount = 0;
        cout << "\n" << "Enter Transfer Amount? ";
        TransferAmount = clsInputValidate::ReadDoubleNumber();

        while(!ClientFrom.HasEnoughMoney(TransferAmount))
        {
            cout << "\n" <<"Amount Exceeds the avaliable balance, Enter another amount : ";
            TransferAmount = clsInputValidate::ReadDoubleNumber();
        }

        char Answer = 'n';
        cout << "\n" << "Are you sure you want to perform this operation? y/n? ";
        cin >> Answer;

        if(tolower(Answer)=='y')
        {
            ClientFrom.Transfer(ClientTo,TransferAmount);
            cout << "\nTransfer Done Successfully\n";
            _PrintClient(ClientFrom);
            _PrintClient(ClientTo);
        }

    }

};