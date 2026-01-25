#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsMainScreen.h"
#include "Global.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{

    private:
    static void _ClearScreen()
    {
        system("clear");
    }

    static void _Login()
    {

        string Username,Password;
        bool LoginFailed = false;

        do
        {

            if(LoginFailed)
            {
                cout << "\n" << "Invalid username/password.";
            }

            cout << "\n" << "Enter username : ";
            Username = clsInputValidate::ReadString();

            cout << "\n" << "Enter Password : ";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsBankUser::Find(Username,Password);

            LoginFailed = CurrentUser.IsEmpty();


        } while (LoginFailed);


        clsMainScreen::ShowMainMenue();
    }

    public:
    static void ShowLoginScreen()
    {
        _ClearScreen();
        _DrawScreenHeader("\t\tLogin Screen");
        _Login();
    }
};