#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long BigInt;

bool IsSpecial(BigInt number)
{
    number = number * number;
    bool hasZero = false, hasFour = false, hasNine = false;

    while (number != 0)
    {
        if (number % 10 == 0)
        {
            hasZero = true;
        }
        else if (number % 10 == 4)
        {
            hasFour = true;
        }
        else if (number % 10 == 9)
        {
            hasNine = true;
        }
        else
        {
            return false;
        }

        number /= 10;
    }

    return (hasZero && hasFour && hasNine);
}

BigInt GetNthSpecialNumber(int n)
{
    int specialNumbersPassed = 0;
    for (BigInt i = 70; i < 10000000000; i++)
    {
        if (i % 10 == 1 || i % 10 == 4 || i % 10 == 5 || i % 10 == 6 || i % 10 == 8)
        {
            continue;
        }
        if (IsSpecial(i))
        {
            if (specialNumbersPassed == n - 1)
            {
                return i;
            }
            specialNumbersPassed++;
        }
    }

    return -1;
}

int main()
{
    int index = 1;
    for (BigInt i = 70; true; i++)
    {
        if (i % 10 == 1 || i % 10 == 4 || i % 10 == 5 || i % 10 == 6 || i % 10 == 8)
        {
            continue;
        }
        if (IsSpecial(i))
        {
            cout << index++ << " " << i << endl;
        }
    }

    return 0;
}
