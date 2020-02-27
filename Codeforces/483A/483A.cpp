#include <iostream>

using namespace std;
typedef long long BigInt;

BigInt GCD(BigInt x, BigInt y)
{
    while (y != 0)
    {
        BigInt t = x;
        x = y;
        y = t % y;
    }

    return x;
}

int main()
{
    BigInt l, r;
    cin >> l >> r;

    for (BigInt a = l; a <= r; a++)
    {
        for (BigInt b = a + 1; b <= r; b++)
        {
            for (BigInt c = b + 1; c <= r; c++)
            {
                if (GCD(a, b) == 1 && GCD(b, c) == 1 && GCD(a, c) != 1)
                {
                    cout << a << " " << b << " " << c << endl;
                    return 0;
                }
            }
        }
    }

    cout << -1 << endl;

    return 0;
}
