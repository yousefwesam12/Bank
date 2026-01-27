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

    static bool _Login()
    {

        string Username,Password;
        short FailedLoginCount = 0;
        bool LoginFailed = false;
        do
        {

            if(LoginFailed)
            {
                FailedLoginCount++;
                cout << "\n" << "Invalid username/password.";
                cout << "\n" << "You have " << 3 - FailedLoginCount << " Trials to login.\n";

                if(FailedLoginCount == 3)
                {
                    cout << "\n" << "You are locked after 3 failed trails.";
                    return false;
                }
            }

            cout << "\n" << "Enter username : ";
            Username = clsInputValidate::ReadString();

            cout << "\n" << "Enter Password : ";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsBankUser::Find(Username,Password);

            LoginFailed = CurrentUser.IsEmpty();


        } while (LoginFailed);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();

        return true;
    }

    public:
    static bool ShowLoginScreen()
    {
        _ClearScreen();
        _DrawScreenHeader("\t\tLogin Screen");
        return _Login();
    }

};