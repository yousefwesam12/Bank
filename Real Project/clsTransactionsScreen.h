#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clswithdrawScreen.h"
#include "clsTotalBalacnesScreen.h"
#include "clsTransferScreen.h"
using namespace std;


class clsTransactionsScreen : protected clsScreen
{


    private:
    enum _enTransactionsChoices 
    {
        enDeposit = 1, enWithdraw = 2, enShowTotalBalances = 3,
        enTransfer = 4,enGoBackToMainMenue = 5
    };
    
    static short _ReadTransactionsChoice()
    {
        short Choice = 0;
        cout << setw(37)  << left << "" << "Enter your choice? [1 to 5]? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1,5);
        return Choice;
    }
       static void _ClearScreen()
    {
        system("clear");
    }
    static void _GoBackToTransactionsMenue()
    {
        cout << "Press any key to go back to Transactions Menue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        _ClearScreen();
        ShowTransactionsScreen();
    }
    
    static void _PerformTransactionsMenue(_enTransactionsChoices TransactionChoice)
    {
        switch (TransactionChoice)
        {
            case enDeposit:
            _ClearScreen();
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;

            case enWithdraw:
            _ClearScreen();
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;

            case enShowTotalBalances:
            _ClearScreen();
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;

            case enTransfer:
            _ClearScreen();
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;

            case enGoBackToMainMenue:
            // Do nothing here, the main screen will handle it (-:
            // Becuase it will call GoBackToMainMenueScreen().        
        }
    }

    static void _ShowDepositScreen()
    {
        //cout << "\n" << "Deposit Screen Will Be Here..\n";
        clsDepositScreen::ShowDepositScreen();
    }
    
    static void _ShowWithdrawScreen()
    {
        //cout << "\n" << "Withdraw Screen Will Be Here..\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        //cout << "\n" << "Total Balances Screen Will Be Here..\n";
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _ShowTransferScreen()
    {
        // Transfer Screen Will be here.
        clsTransferScreen::ShowTransferScreen();
    }

    public:
    static void ShowTransactionsScreen()
    {
         if(!CurrentUser.HasAccessToThisPermission(clsBankUser::pTransactions))
        {
            ShowAccessDeniedMessage();
            return;
        }
            _ClearScreen();
            _DrawScreenHeader("\t Transactions Screen");
            cout << setw(37)  << left  << "" << "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t\tTransactions Menue\n";
            cout << setw(37) << left << ""  <<  "===========================================\n";
            cout << setw(37) << left << ""  <<  "\t[1] Deposit.\n";
            cout << setw(37) << left << ""  <<  "\t[2] Withdraw.\n";
            cout << setw(37) << left << ""  <<  "\t[3] Total Balances.\n";
            cout << setw(37) << left << ""  <<  "\t[4] Transfer.\n";
            cout << setw(37) << left << ""  <<  "\t[5] Main Menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            _PerformTransactionsMenue(_enTransactionsChoices(_ReadTransactionsChoice()));
    
    }
};