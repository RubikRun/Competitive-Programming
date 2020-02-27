/*
ID: borisd22
TASK: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("crypt1.out");
ifstream fin ("crypt1.in");

#define MaxNumberOfAllowedDigits 10

bool HasUnallowedDigits(int number, int allowedDigits[], int numberOfAllowedDigits)
{
    bool isAllowed;
    while (number != 0)
    {
        isAllowed = false;
        for (int i = 0; i < numberOfAllowedDigits; i++)
        {
            if (allowedDigits[i] == number % 10)
            {
                isAllowed = true;
                break;
            }
        }

        if (!isAllowed)
        {
            return true;
        }

        number /= 10;
    }

    return false;
}

int GetNumberOfSolutions(int allowedDigits[], int numberOfAllowedDigits)
{
    int numberOfSolutions = 0;

    for (int digitIndex1 = 0; digitIndex1 < numberOfAllowedDigits; digitIndex1++)
    {
        if (allowedDigits[digitIndex1] == 0)
        {
            continue;
        }
        for (int digitIndex2 = 0; digitIndex2 < numberOfAllowedDigits; digitIndex2++)
        {
            for (int digitIndex3 = 0; digitIndex3 < numberOfAllowedDigits; digitIndex3++)
            {
                for (int digitIndex4 = 0; digitIndex4 < numberOfAllowedDigits; digitIndex4++)
                {
                    if (allowedDigits[digitIndex4] == 0)
                    {
                        continue;
                    }
                    for (int digitIndex5 = 0; digitIndex5 < numberOfAllowedDigits; digitIndex5++)
                    {

                        int number1 = allowedDigits[digitIndex1] * 100 + allowedDigits[digitIndex2] * 10 + allowedDigits[digitIndex3];
                        int number2 = allowedDigits[digitIndex4] * 10 + allowedDigits[digitIndex5];

                        int partial1 = (number2 % 10) * number1;
                        int partial2 = (number2 / 10) * number1;

                        if (partial1 / 100 <= 0 || partial1 / 100 >= 10)
                        {
                            continue;
                        }
                        if (partial2 / 100 <= 0 || partial2 / 100 >= 10)
                        {
                            continue;
                        }
                        if (HasUnallowedDigits(partial1, allowedDigits, numberOfAllowedDigits))
                        {
                            continue;
                        }
                        if (HasUnallowedDigits(partial2, allowedDigits, numberOfAllowedDigits))
                        {
                            continue;
                        }

                        int final = partial1 + partial2 * 10;
                        if (final / 1000 <= 0 || final / 1000 >= 10)
                        {
                            continue;
                        }
                        if (HasUnallowedDigits(final, allowedDigits, numberOfAllowedDigits))
                        {
                            continue;
                        }

                        numberOfSolutions++;
                        cout << number1 << " " << number2 << " " << partial1 << " " << partial2 << " " << final << endl;
                    }
                }
            }
        }
    }

    return numberOfSolutions;
}

int main()
{
    int numberOfAllowedDigits;
    fin >> numberOfAllowedDigits;
    int allowedDigits[MaxNumberOfAllowedDigits];
    for (int i = 0; i < numberOfAllowedDigits; i++)
    {
        fin >> allowedDigits[i];
    }

    int numberOfSolutions = GetNumberOfSolutions(allowedDigits, numberOfAllowedDigits);
    fout << numberOfSolutions << endl;

    return 0;
}