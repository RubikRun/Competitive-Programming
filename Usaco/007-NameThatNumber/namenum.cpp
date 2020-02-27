/*
ID: borisd22
TASK: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

ofstream fout ("namenum.out");
ifstream fin ("namenum.in");

#define MaxNumberOfValidNames 5000
#define MaxNameLen 13
#define NumberOfPhoneKeys 10

char validNames[MaxNumberOfValidNames][MaxNameLen];
int numberOfValidNames;

int printedAnything;

char phoneKeyboard[NumberOfPhoneKeys][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {'A', 'B', 'C'},
        {'D', 'E', 'F'},
        {'G', 'H', 'I'},
        {'J', 'K', 'L'},
        {'M', 'N', 'O'},
        {'P', 'R', 'S'},
        {'T', 'U', 'V'},
        {'W', 'X', 'Y'}
};

void SwapEm(int& a, int& b)
{
    int holder = a;
    a = b;
    b = holder;
}

void ReadValidNames()
{
    ifstream dictIn ("dict.txt");
    numberOfValidNames = 0;

    while (dictIn >> validNames[numberOfValidNames])
    {
        numberOfValidNames++;
    }
}

bool NamesEqual(char name1[], char name2[])
{
    int l1 = strlen(name1);
    int l2 = strlen(name2);

    if (l1 != l2)
    {
        return false;
    }

    for (int i = 0; i < l1; i++)
    {
        if (name1[i] != name2[i])
        {
            return false;
        }
    }

    return true;
}

bool NameGreaterThan(char name1[], char name2[])
{
    int l1 = strlen(name1);
    int l2 = strlen(name2);
    int l = min(l1, l2);

    for (int i = 0; i < l; i++)
    {
        if (name1[i] > name2[i])
        {
            return true;
        }
        else if (name1[i] < name2[i])
        {
            return false;
        }
    }

    if (l1 > l2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool NameIsValid(char name[], int nameLen)
{
    int first = 0, last = numberOfValidNames - 1;
    int mid;

    while (last - first > 5)
    {
        mid = (first + last) / 2;
        if (NamesEqual(name, validNames[mid]))
        {
            return true;
        }
        if (NameGreaterThan(name, validNames[mid]))
        {
            first = mid + 1;
        }
        else
        {
            last = mid - 1;
        }
    }

    for (int i = first; i <= last; i++)
    {
        if (NamesEqual(name, validNames[i]))
        {
            return  true;
        }
    }

    return false;
}

void PrintIfValidName(int digits[], int buttonChoices[], int numberOfDigits)
{
    char name[MaxNameLen];
    for (int i = 0; i < numberOfDigits; i++)
    {
        name[i] = phoneKeyboard[digits[i]][buttonChoices[i]];
    }
    name[numberOfDigits] = '\0';

    if (NameIsValid(name, numberOfDigits))
    {
        fout << name << endl;
        printedAnything = true;
    }
}

bool NextCombination(int buttonChoices[], int numberOfButtons)
{
    for (int i = numberOfButtons - 1; i >= 0; i--)
    {
        if (buttonChoices[i] < 2)
        {
            buttonChoices[i]++;
            for (int j = i + 1; j < numberOfButtons; j++)
            {
                buttonChoices[j] = 0;
            }
            return true;
        }
    }

    return false;
}

void PrintValidNames(int digits[], int numberOfDigits)
{
    int buttonChoices[MaxNameLen];
    for (int i = 0; i < numberOfDigits; i++)
    {
        buttonChoices[i] = 0;
    }

    do
    {
        PrintIfValidName(digits, buttonChoices, numberOfDigits);
    } while (NextCombination(buttonChoices, numberOfDigits));
}

int main()
{
    ReadValidNames();
    printedAnything = false;

    char digitsString[MaxNameLen];
    fin >> digitsString;
    int digits[MaxNameLen];
    int numberOfDigits = strlen(digitsString);
    for (int i = 0; i < numberOfDigits; i++)
    {
        digits[i] = digitsString[i] - '0';
    }

    PrintValidNames(digits, numberOfDigits);

    if (!printedAnything)
    {
        fout << "NONE" << endl;
    }

    return 0;
}

