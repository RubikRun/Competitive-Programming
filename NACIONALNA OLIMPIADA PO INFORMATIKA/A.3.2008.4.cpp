//checked - 80%

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
#define ArrLen 12
#define MaxNumberOfDigits 50

int arr[ArrLen];
int factor;

int factorial[ArrLen + 1] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int ReadNumberMod6()
{
    char digits[MaxNumberOfDigits];
    cin >> digits;
    int numberOfDigits = strlen(digits);

    int mod2 = digits[numberOfDigits - 1] % 2;
    int mod3 = 0;
    for (int i = 0; i < numberOfDigits; i++)
    {
        mod3 = (mod3 + digits[i] % 3) % 3;
    }

    int mod6 = mod3;
    if (mod3 % 2 != mod2)
    {
        mod6 += 3;
    }

    return mod6;
}

void FindFactor()
{
    factor = 1;

    for (int i = 0; i < 6; i++)
    {
        int count = 0;
        for (int j = 0; j < ArrLen; j++)
        {
            if (arr[j] == i)
            {
                count++;
            }
        }
        factor *= factorial[count];
    }
}

void Input()
{
    for (int i = 0; i < ArrLen; i++)
    {
        arr[i] = ReadNumberMod6();
    }
    sort(arr, arr + ArrLen);
}

bool PermIsCorrect()
{
    for (int i = 0; i < 3; i++)
    {
        int sum = 0;
        for (int j = 0; j < 4; j++)
        {
            sum += arr[i * 4 + j];
        }
        if (sum % 2 != 0)
        {
            return false;
        }
    }

    for (int j = 0; j < 4; j++)
    {
        int sum = 0;
        for (int i = 0; i < 3; i++)
        {
            sum += arr[i * 4 + j];
        }
        if (sum % 3 != 0)
        {
            return false;
        }
    }

    return true;
}

int GetCount()
{
    int count = 0;

    do {
        if (PermIsCorrect())
        {
            count++;
        }
    } while(next_permutation(arr, arr + ArrLen));

    return count * factor / 144;
}

void Solve()
{
    Input();
    FindFactor();
    cout << GetCount() << endl;
}

int main()
{
    Solve();
    Solve();

    return 0;
}
