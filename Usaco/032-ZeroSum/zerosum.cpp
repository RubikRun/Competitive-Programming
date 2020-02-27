/*
ID: borisd22
TASK: zerosum
LANG: C++
*/

#include <fstream>

using namespace std;

ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

#define MaxNumberOfDigits 9

int choices[MaxNumberOfDigits + 1];
int numberOfDigits;

void InitChoices()
{
    for (int i = 1; i < numberOfDigits; i++)
    {
        choices[i] = 0;
    }
}

bool NextChoices()
{
    for (int i = numberOfDigits - 1; i >= 1; i--)
    {
        if (choices[i] == 2)
        {
            choices[i] = 0;
        }
        else
        {
            choices[i]++;
            return true;
        }
    }

    return false;
}

bool IsZeroSum()
{
    int factor = 1;
    int sum = 0;
    int term = 1;
    for (int i = 1; i < numberOfDigits; i++)
    {
        if (choices[i] == 0)
        {
            term *= 10;
            term += i + 1;
        }
        else
        {
            sum += term * factor;
            term = i + 1;
            factor = (choices[i] == 1) ? 1 : -1;
        }
    }
    sum += term * factor;

    return (sum == 0);
}

void PrintZeroSums()
{
    InitChoices();

    do
    {
        if (IsZeroSum())
        {
            for (int i = 1; i < numberOfDigits; i++)
            {
                fout << i;
                if (choices[i] == 1)
                {
                    fout << "+";
                }
                else if (choices[i] == 2)
                {
                    fout << "-";
                }
                else
                {
                    fout << " ";
                }
            }
            fout << numberOfDigits << endl;
        }
    } while (NextChoices());
}

int main()
{
    numberOfDigits;
    fin >> numberOfDigits;

    PrintZeroSums();

    return 0;
}