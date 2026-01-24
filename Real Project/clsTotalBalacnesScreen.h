#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{

    private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(40) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.GetAccountBalance();
    }


    public:
    static void ShowTotalBalancesScreen()
    {
         vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title,SubTitle);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
   
    cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << setw(25) << left << "";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << clsUtil::Tabs(4) <<"No Clients Available In the System!";

    else
        for (clsBankClient &Client : vClients)
        {
            _PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = clsBankClient::GetTotalBalances();

    cout << clsUtil::Tabs(5) << " Total Balances = " << TotalBalances << endl;
    cout << clsUtil::Tabs(5) << "( " << clsUtil::NumberToText(TotalBalances) << " )" << endl;
    }
};
