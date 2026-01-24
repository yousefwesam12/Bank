#include <iostream>
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsDeleteUserScreen : protected clsScreen
{
    private:
    static void _PrintUser(clsBankUser User)
    {
        cout << "\n\t User Card\n";
        cout << "===============================";
        cout << "\n" << "Username : " << User.GetUsername();
        cout << "\n" << "Email    : " << User.GetEmail();
        cout << "\n" << "Phone    : " << User.GetPhone();
        cout << "\n" << "Password : " << User.GetPassword();
        cout << "\n" << "Permissions:"<<User.GetPermissions();
        cout << "\n===============================\n";
    }

    public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\tDelete User Screen");

        string Username = "";
        cout << "\n" << "Enter username of the target user: ";
        Username = clsInputValidate::ReadString();

        while(!clsBankUser::IsUserExist(Username))
        {
            cout << "User with this username is not exist, enter a different one: ";
            Username = clsInputValidate::ReadString();
        }

        clsBankUser User = clsBankUser::Find(Username);
        _PrintUser(User);

        char answer = 'n';

        cout << "\n" << "Are you sure you want to delete this user from the system? Y/N? ";
        cin >> answer;

        if(tolower(answer) == 'y')
        {
            if(User.Delete())
            {
                cout << "\nUser Deleted Successfully.\n";
                _PrintUser(User);
            }
        }
        else
        {
            cout << "Deletion has been cancelled.\n";
        }
    }

};