#pragma once
#include <iostream>
#include "clsDate.h"

using namespace std;

class clsUtil
{
    public:
    static void Srand()
    {
        srand((unsigned)time(NULL));
    }
    
    static int RandomNumber(const int From,const int To)
    {
        return rand() % (To-From+1) + From;
    }
    enum enCharType {CapitalLetter=1,SmallLetter,Digit,MixChars,Special}; 
    static char GetRandomChar(enCharType CharType)
    {
        if(CharType == MixChars)
        {
            CharType = enCharType(RandomNumber(1,3));
        }

        switch(CharType)
        {
            case CapitalLetter:
                return char(RandomNumber(65,90));
            case SmallLetter:
                return char(RandomNumber(97,122));
            case Special:
                return char(RandomNumber(33,47));
            case Digit:
                return char(RandomNumber(48,57)); 
            default:
                return char(RandomNumber(65,90)); 
                break;
        }
    }
    static string GenerateWord(enCharType CharType,short Length)
    {
        string Word;

        for (int i = 0;i<Length;i++)
        {
            Word += GetRandomChar(CharType);
        }
        return Word;
    }
    static string GenerateKey(enCharType CharType)
    {
        string Key;

        Key  = GenerateWord(CharType,4) + "-";
        Key += GenerateWord(CharType,4) + "-";
        Key += GenerateWord(CharType,4) + "-";
        Key += GenerateWord(CharType,4);

        return Key;
    }
    static void GenerateKeys(short NumOfKeys,enCharType CharType)
    {
        for(int i = 1;i<=NumOfKeys;i++)
        {
            cout << "Key ["<<i<<"] : ";
            cout << GenerateKey(CharType);
            cout << "\n";
        }
    }
    static void Swap(int &A,int &B)
    {
        int Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(bool& A, bool& B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(char& A, char& B)
    {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(double &A,double &B)
    {
        double Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(string &A,string &B)
    {
        string Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(clsDate &Date1,clsDate &Date2)
    {
        clsDate::SwapDates(Date1,Date2);
    }
    static void ShuffleArray(int Arr1[],int ArrLen)
    {
        // {1,2,3,4,5}
        // {2,3,1,4,5}
        for(int i = 0;i<ArrLen;i++)
        {
            Swap(Arr1[RandomNumber(1,ArrLen)-1],Arr1[RandomNumber(1,ArrLen)-1]);
        }
    }
    static void ShuffleArray(string Arr1[],int ArrLen)
    {
        // {1,2,3,4,5}
        // {2,3,1,4,5}
        for(int i = 0;i<ArrLen;i++)
        {
            Swap(Arr1[RandomNumber(1,ArrLen)-1],Arr1[RandomNumber(1,ArrLen)-1]);
        }
    }
    static void FullArrayWithRandomNumbers(int Arr1[],int ArrLen,int From,int To)
    {
        for(int i = 0;i<ArrLen;i++)
        {
            Arr1[i] = RandomNumber(From,To);
        }
    }
    static void FullArrayWithRandomWords(string Arr1[],int ArrLen,enCharType CharType,int WordLen)
    {
        for(int i = 0;i<ArrLen;i++)
        {
            Arr1[i] = GenerateWord(CharType,WordLen);
        }
    }
    static void FullArrayWithRandomWords(string Arr1[],int ArrLen,enCharType CharType)
    {
        for(int i = 0;i<ArrLen;i++)
        {
            Arr1[i] = GenerateKey(CharType);
        }
    }
    static string Tabs(short NumOfTabs)
    {
        string T = "";

        for (int i = 1;i<=NumOfTabs;i++)
        {
            T += "\t";
        }
        return T;
    }
    static string EncryptText(string Text,short Key)
    {
        for(int i = 0;i<Text.length();i++)
        {
            Text[i] = char(int(Text[i]) + Key);
        }
        return Text;
    }
    static string DecryptText(string Text,short Key)
    {
        for(int i = 0;i<Text.length();i++)
        {
            Text[i] = char(int(Text[i]) - Key);
        }
        return Text;
    }
    static string NumberToText(long long Number)
    {

    if (Number == 0)
    {
        return "";
    }

    if (Number>=1 && Number <=19)
    {
        string Arr[] =
            {"","One","Two","Three","Four","Five","Six","Seven",
            "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen"
            ,"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};

        return Arr[Number];
    }
    if (Number>=20 && Number<=99)
    {
        string Arr[] = {"","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
        return Arr[Number/10] + " " + NumberToText(Number%10);
    }
    if (Number>=100 && Number<=199)
    {
        return "One Hundred " + NumberToText(Number%100);
    }
    if (Number>=200 && Number <=999)
    {
        return NumberToText(Number/100) + " Hundreds " + NumberToText(Number%100);
    }
    if (Number>=1000 && Number<=1999)
    {
        return "One Thousands " + NumberToText(Number%1000);
    }
    if (Number>=2000 && Number<=999999)
    {
        return NumberToText(Number/1000) + " Thousands " + NumberToText(Number%1000);
    }
    if (Number>=1000000 && Number<=1999999)
    {
        return "One Million " + NumberToText(Number%1000000);
    }
    if (Number>=2000000 && Number<=9999999)
    {
        return NumberToText(Number/1000000) + " Million " + NumberToText(Number%1000000);
    }
    if (Number>=10000000 && Number<=19999999)
    {
        return "One Billion " + NumberToText(Number%10000000);
    }
    else
    {
        return NumberToText(Number/10000000) + " Billion " + NumberToText(Number%10000000);
    }

    }
    
    
};
