#include <iostream>

using namespace std;
typedef long long BigInt;

BigInt GetNumberOfDivisors(BigInt x)
{
    BigInt numberOfDivisors = 1;
    BigInt power = 0;
    while (x % 2 == 0)
    {
        x /= 2;
        power++;
    }
    numberOfDivisors *= (power + 1);

    for (BigInt divisor = 3; divisor * divisor <= x; divisor += 2)
    {
        BigInt power = 0;
        while (x % divisor == 0)
        {
            x /= divisor;
            power++;
        }

        numberOfDivisors *= (power + 1);
    }

    if (x > 2)
    {
        numberOfDivisors *= 2;
    }

    return numberOfDivisors;
}

int main()
{
    BigInt b;
    cin >> b;

    cout << GetNumberOfDivisors(b) << endl;

    return 0;
}
