#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
    static double _ReadAmount()
    {
    
        double TransferAmount = 0;
        do
        {
            cout << "\n" << "Enter Transfer Amount? ";
            TransferAmount = clsInputValidate::ReadDoubleNumber();

        } while (TransferAmount<=0);

        return TransferAmount;
    
    }
    
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
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer From: "));
        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer To: "));
        _PrintClient(DestinationClient);

        double TransferAmount = _ReadAmount();

        char Answer = 'n';
        cout << "\n" << "Are you sure you want to perform this operation? y/n? ";
        cin >> Answer;

        if(tolower(Answer)=='y')
        {

            if(SourceClient.Transfer(DestinationClient,TransferAmount))
            {
                cout << "\nTransfer Done Successfully\n";
            }
            else
            {
                cout << "\nTransfer Failed\n";
            }

        }
             _PrintClient(SourceClient);
            _PrintClient(DestinationClient);

    }

};