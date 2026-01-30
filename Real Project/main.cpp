#include <iostream>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
#include "clsInputValidate.h"
using namespace std;



int main()
{

    while(true)
    {
        if(!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
   

}
