#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
    clsPerson(string FirstName,string LastName,string Email,string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Phone = Phone;
        _Email = Email;
    }

    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    string GetFirstName()
    {
        return _FirstName;
    }
    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }
    string GetLastName()
    {
        return _LastName;
    }
    void SetEmail(string Email)
    {
       _Email = Email;
    }
    string GetEmail()
    {
        return _Email;
    }
    string GetFullName()
    {
        return GetFirstName() + "  " + GetLastName();
    }
    void SetPhone(string _Phone)
    {
        this->_Phone = _Phone;
    }
    string GetPhone()
    {
        return this->_Phone;
    }
};
