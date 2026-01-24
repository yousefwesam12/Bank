#pragma once
#include <iostream>
#include <fstream>
#include "clsUtil.h"
#include "clsString.h"
#include "clsPerson.h"

class clsBankClient : public clsPerson
{
    private:
    enum enMode {EmptyMode = 0, UpdateMode = 1,AddNewMode = 2};
    enMode  _Mode;
    string  _AccountNumber;
    string  _PinCode;
    double  _AccountBalance;
    bool    _MarkedForDelete = false;

    static clsBankClient _ConvertLineToClientObject(string Line,string Sep = "#//#")
    {
        vector <string> vClientData = clsString::Split(Line,Sep);

        return clsBankClient(enMode::UpdateMode,vClientData[0],vClientData[1],vClientData[2],vClientData[3],vClientData[4],vClientData[5],stod(vClientData[6]));
    }
    
    string _ConvertClientObjectToLine(clsBankClient Client,string Sep = "#//#")
    {
        string Line = "";
        Line += Client.GetFirstName() + Sep;
        Line += Client.GetLastName()  + Sep;
        Line += Client.GetPhone()     + Sep;
        Line += Client.GetEmail()     + Sep;
        Line += Client.GetAccountNumber() + Sep;
        Line += Client.GetPinCode()   + Sep;
        Line += to_string(Client.GetAccountBalance());
        return Line;
    }
    
    static vector <clsBankClient> _LoadClientsDataFromFile()
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt",ios::in);

        
        if(MyFile.is_open())
        {

            string Line;

            while(getline(MyFile,Line))
            {
                clsBankClient C = _ConvertLineToClientObject(Line);

                vClients.push_back(C);
            }

            MyFile.close();
        }

        return vClients;
    }
    
    void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt",ios::out);
        string stDataLine = "";

        if(MyFile.is_open())
        {

            for (clsBankClient &C : vClients)
            {
                if(C.GetMarkedForDelete() == false)
                {
                    stDataLine = _ConvertClientObjectToLine(C);
                    
                    MyFile << stDataLine << endl;

                }
            }

            MyFile.close();

        }
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;

        MyFile.open("Clients.txt",ios::out|ios::app);

        if(MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    void _Update()
    {

        vector <clsBankClient> vClients = _LoadClientsDataFromFile();


        for (clsBankClient &C : vClients)
        {
            if(C._AccountNumber == GetAccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);

    }   

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode,"","","","","","",0);
    }

    public:
    clsBankClient(enMode Mode,string FirstName,string LastName,string Phone,string Email,string AccountNumber,string PinCode,double AccountBalance)
    : clsPerson(FirstName,LastName,Email,Phone)
    {
        _Mode           = Mode;
        _AccountNumber  = AccountNumber;
        _PinCode        = PinCode;
        _AccountBalance = AccountBalance;
    }
    void SetAccountNumber(string AccountNumber)
    {
        this->_AccountNumber = AccountNumber;
    }
    string GetAccountNumber()
    {
        return this->_AccountNumber;
    }
      void SetPinCode(string PinCode)
    {
        this->_PinCode = PinCode;
    }
    string GetPinCode()
    {
        return this->_PinCode;
    }
    void SetAccountBalance(double AccountBalance)
    {
        this->_AccountBalance = AccountBalance;
    }
    double GetAccountBalance()
    {
        return this->_AccountBalance;
    }
    bool GetMarkedForDelete()
    {
        return this->_MarkedForDelete;
    }

    
    static clsBankClient Find(string AccountNumber)
    {
        // return the target object otherwise return an empty object.

        fstream MyFile;
        MyFile.open("Clients.txt",ios::in);

        if (MyFile.is_open())
        {

            string Line;

            while(getline(MyFile,Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client._AccountNumber == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }
    
    static clsBankClient Find(string AccountNumber,string PinCode)
    {
        // return the target object otherwise return an empty object.

        fstream MyFile;
        MyFile.open("Clients.txt",ios::in);

        if (MyFile.is_open())
        {

            string Line;

            while(getline(MyFile,Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client._AccountNumber == AccountNumber && Client._PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }
    
    bool IsEmpty()
    {
        return this->_Mode == enMode::EmptyMode;
    }
    
    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = Find(AccountNumber);

        return !(Client.IsEmpty());
    }
    
    enum enSaveResults {enSaveFailedEmptyObject = 0,enSaveSucceeded = 1,SvFailedAccountNumberExists = 2};

    enSaveResults Save()
    {
        switch (_Mode)
        {
            case EmptyMode:

                if(IsEmpty())
                {
                    return enSaveFailedEmptyObject;
                }

            case UpdateMode:
                 _Update();
                return enSaveSucceeded;
            
            case AddNewMode:
                _AddNew();
                this->_Mode = UpdateMode;
                return enSaveSucceeded; 
        }
    }
    
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(AddNewMode,"","","","",AccountNumber,"",0);
    }

    bool Delete()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : vClients)
        {
            if(C.GetAccountNumber() == GetAccountNumber())
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }
    static double GetTotalBalances()
    {
        double TotalBalances = 0;
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : vClients)
        {
            TotalBalances += C.GetAccountBalance();
        }

        return TotalBalances;
    }
    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if(Amount > _AccountBalance)
        {
            return false;
        }
        else
        {

            _AccountBalance -= Amount;
            Save(); 
        }
        return true;
    }
};