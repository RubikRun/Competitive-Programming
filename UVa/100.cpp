#include <iostream>
#include <algorithm>

using namespace std;
typedef long long BigInt;

BigInt GetCycleLength(BigInt x)
{
    BigInt cycleLength = 1;
    while (x != 1)
    {
        x = (x % 2 == 0) ? x / 2 : 3 * x + 1;
        cycleLength++;
    }
    return cycleLength;
}

BigInt GetMaxCycleLength(BigInt a, BigInt b)
{
    BigInt maxCycleLength = 1;
    for (BigInt i = a; i <= b; i++)
    {
        maxCycleLength = max(maxCycleLength, GetCycleLength(i));
    }
    return maxCycleLength;
}

int main()
{
    BigInt a, b;
    while (cin >> a >> b)
    {
        cout << a << " " << b << " " << GetMaxCycleLength(min(a, b), max(a, b)) << endl;
    }
    return 0;
}
