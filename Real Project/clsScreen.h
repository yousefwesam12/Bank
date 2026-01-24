#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h"

using namespace std;

class clsScreen
{

    protected:
    static void _DrawScreenHeader(string Title,string SubTitle = "")
    {
        cout << clsUtil::Tabs(5) << "______________________________________";
        cout << "\n\n" << clsUtil::Tabs(5) << " " << Title;

        if (SubTitle != "")
        {
            cout << "\n" << clsUtil::Tabs(5) << SubTitle;
        }
        cout << "\n" << clsUtil::Tabs(5) << "______________________________________\n\n";
    }
};