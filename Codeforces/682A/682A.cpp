#include <iostream>

using namespace std;
typedef long long BigInt;

BigInt phi(BigInt n, BigInt k)
{
    return (n + (5 - k) % 5) / 5;
}

BigInt f(BigInt n, BigInt m)
{
    BigInt r = 0;
    for (BigInt i = 0; i < 5; i++)
    {
        r += phi(n, i) * phi(m, (5 - i) % 5);
    }
    return r;
}

int main()
{
    BigInt n, m;
    cin >> n >> m;
    cout << f(n, m) << endl;
    return 0;
}
