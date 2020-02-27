/*
ID: borisd22
TASK: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("dualpal.out");
ifstream fin ("dualpal.in");

#define MaxNumberOfWantedDualpals 15
#define MaxNumberOfDigits 32

void FindDigits(int number, int base, int digits[], int& numberOfDigits)
{
    numberOfDigits = 0;

    while (number != 0)
    {
        digits[numberOfDigits++] = number % base;
        number /= base;
    }
}

bool IsPalInBase(int number, int base)
{
    int digits[MaxNumberOfDigits], numberOfDigits;
    FindDigits(number, base, digits, numberOfDigits);

    for (int index = 0; index < numberOfDigits / 2; index++)
    {
        if (digits[index] != digits[numberOfDigits - index - 1])
        {
            return false;
        }
    }

    return true;
}

bool IsDualpal(int number)
{
    int numberOfPalBases = 0;

    for (int base = 2; base <= 10 && numberOfPalBases < 2; base++)
    {
        if (IsPalInBase(number, base))
        {
            numberOfPalBases++;
        }
    }

    return numberOfPalBases >= 2;
}

void FindWantedDualpals(int wantedDualpals[], int numberOfWantedDualpals, int lowerLimit)
{
    int numberOfFoundDualpals = 0;
    int potentialDualpal = lowerLimit + 1;

    while (numberOfFoundDualpals < numberOfWantedDualpals)
    {
        if (IsDualpal(potentialDualpal))
        {
            wantedDualpals[numberOfFoundDualpals++] = potentialDualpal;
        }

        potentialDualpal++;
    }
}

int main()
{
    int numberOfWantedDualpals;
    fin >> numberOfWantedDualpals;
    int lowerLimit;
    fin >> lowerLimit;

    int wantedDualpals[MaxNumberOfWantedDualpals];
    FindWantedDualpals(wantedDualpals, numberOfWantedDualpals, lowerLimit);

    for (int dualpalIndex = 0; dualpalIndex < numberOfWantedDualpals; dualpalIndex++)
    {
        fout << wantedDualpals[dualpalIndex] << endl;
    }

    return 0;
}