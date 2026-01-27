#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>
#include "clsLoginScreen.h"

int main()
{
    while(true)
    {

        if(!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

    return 0;
}