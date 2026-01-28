#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>

class clsBankUser : public clsPerson
{
    private:
    enum enMode {eEmptyMode = 1, eUpdateMode = 2, eAddNewMode = 3};
    enMode _Mode;
    string _Username;
    string _Password;
    short  _Permissions;
    bool   _MarkedForDelete = false;

    static clsBankUser _ConvertUserLineToObject(string Line,string Sep = "#//#")
    {
        //Adli#//#Haddad#//#Adli@Gmail.com#//#8983883#//#User1#//#1234#//#-1
        vector <string> vUserData = clsString::Split(Line,Sep);
        return clsBankUser(eUpdateMode,vUserData[0],vUserData[1],vUserData[2],vUserData[3],vUserData[4],vUserData[5],stoi(vUserData[6]));
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::DateToString(clsDate::GetSystemDate()) + " - ";
        LoginRecord += clsDate::GetSystemTimeString() + Seperator;
        LoginRecord += _Username + Seperator;
        LoginRecord += _Password + Seperator;
        LoginRecord += to_string(_Permissions);
        return LoginRecord;
    }

    static string _ConvertClientObjectToLine(clsBankUser User,string Sep = "#//#")
    {
        string stLine = "";
        stLine += User.GetFirstName() + Sep;
        stLine += User.GetLastName()  + Sep;
        stLine += User.GetEmail()     + Sep;
        stLine += User.GetPhone()     + Sep;
        stLine += User.GetUsername()  + Sep;
        stLine += User.GetPassword()  + Sep;
        stLine += to_string(User.GetPermissions());

        return stLine;
    }

    static vector <clsBankUser> _LoadUsersDataFromFile()
    {
        vector <clsBankUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt",ios::in);

        if(MyFile.is_open())
        {
            string Line;

            while(getline(MyFile,Line))
            {
                vUsers.push_back(_ConvertUserLineToObject(Line));
            }

            MyFile.close();
        }

        return vUsers;
        
    }

    static void _SaveUsersDataToFile(vector <clsBankUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt",ios::out);

        if(MyFile.is_open())
        {
            string stDataLine = " ";

            for (clsBankUser &User : vUsers)
            {
                if(!User._MarkedForDelete)
                {
                    stDataLine = _ConvertClientObjectToLine(User);

                    MyFile << stDataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    static clsBankUser _GetEmptyUserObject()
    {
        return clsBankUser(eEmptyMode,"","","","","","",0);
    }

    void _Update()
    {
        vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

        for (clsBankUser &User : vUsers)
        {
            if(User._Username == GetUsername())
            {
                User = *this;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt",ios::app | ios::out);
        
        if(MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    public:


    enum enPermissions
    {
        pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLogRegister = 128, pTransferLog = 256
    };

    bool HasAccessToThisPermission(enPermissions Permission)
    {   
        if(GetPermissions() == pAll)
        {
            return true;
        }
        
        return ( (GetPermissions() & Permission) == Permission);
    }

    clsBankUser(enMode Mode,string FirstName,string LastName,string Email,string Phone,string Username,string Password,short Permissions)
     : clsPerson(FirstName,LastName,Email,Phone)
    {
        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permissions = Permissions;
    }
    
    void SetUsername(string Username)
    {
        this->_Username = Username;
    }
    string GetUsername()
    {
        return this->_Username;
    }
    void SetPassword(string Password)
    {
        this->_Password = Password;
    }
    string GetPassword()
    {
        return this->_Password;
    }
    void SetPermission(short Permission)
    {
        this->_Permissions = Permission;
    }
    int GetPermissions()
    {
        return this->_Permissions;
    }
    bool GetMarkedForDelete()
    {
        return this->_MarkedForDelete;
    }
    
    enum enSaveResults {svFailedEmptyObject = 0, svSucceeded = 1, svFailedUserExists = 3};

    enSaveResults Save()
    {
        switch(_Mode)
        {
            case eEmptyMode:
                if(this->IsEmpty())
                {
                    return svFailedEmptyObject;
                }
            
            case eUpdateMode:
                _Update();
                return svSucceeded;

            case eAddNewMode:
                if(clsBankUser::IsUserExist(_Username))
                {
                    return svFailedUserExists;
                }
                else
                {
                    _AddNew();
                    _Mode = eUpdateMode;
                    return enSaveResults::svSucceeded;
                }
                break;
                
        }
    }

     bool IsEmpty()
     {
        return (_Mode == eEmptyMode);
     }
    
    static clsBankUser Find(string Username)
     {
        fstream MyFile;
        MyFile.open("Users.txt",ios::in);

        if(MyFile.is_open())
        {

            string Line;

            while(getline(MyFile,Line))
            {
                clsBankUser User = _ConvertUserLineToObject(Line);

                if(User.GetUsername() == Username)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
     }

    static clsBankUser Find(string Username,string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt",ios::in);

        if(MyFile.is_open())
        {

            string Line;

            while(getline(MyFile,Line))
            {
                clsBankUser User = _ConvertUserLineToObject(Line);

                if(User.GetUsername() == Username && User.GetPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static bool IsUserExist(string Username)
    {
        clsBankUser User = Find(Username);

        return !(User.IsEmpty());
    }

    bool Delete()
    {
        fstream MyFile;
        MyFile.open("Users.txt",ios::in);

        vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

        if(MyFile.is_open())
        {   
            for(clsBankUser &User : vUsers)
            {
                if(User._Username == _Username)
                {
                    User._MarkedForDelete = true;
                    break;
                }
            }

            MyFile.close();
        }

        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    static vector <clsBankUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    static clsBankUser GetAddNewUserObject(string Username)
    {
        return clsBankUser(eAddNewMode,"","","","",Username,"",0);
    }

    void RegisterLogIn()
    {
        string stRegisterLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt",ios::out|ios::app);

        if(MyFile.is_open())
        {

            MyFile << stRegisterLine << endl;

            MyFile.close();
        }
    }

    struct stLoginRegisterInfo
    {
        string DateAndTime = "";
        string Username = "";
        string Password = "";
        short Permissions = 0;
    };
      
    static stLoginRegisterInfo ConvertLoginRegisterLineToRecord(string stLoginLine)
    {
        stLoginRegisterInfo RegisterInfo;
        vector <string> vLine = clsString::Split(stLoginLine,"#//#");
        RegisterInfo.DateAndTime = vLine[0];
        RegisterInfo.Username = vLine[1];
        RegisterInfo.Password = vLine[2];
        RegisterInfo.Permissions = stoi(vLine[3]);
        return RegisterInfo;
    };
    
    static vector <stLoginRegisterInfo> GetLoginRegisterInfo()
    {
        vector <stLoginRegisterInfo> vLoginRegisterInfo;

        fstream MyFile;
        MyFile.open("LoginRegister.txt",ios::in);

        if(MyFile.is_open())
        {
            string line;
            stLoginRegisterInfo RegisterInfo;

            while(getline(MyFile,line))
            {
                RegisterInfo = ConvertLoginRegisterLineToRecord(line);
                vLoginRegisterInfo.push_back(RegisterInfo);
            }

            MyFile.close();
        }

            return vLoginRegisterInfo;
    }

};