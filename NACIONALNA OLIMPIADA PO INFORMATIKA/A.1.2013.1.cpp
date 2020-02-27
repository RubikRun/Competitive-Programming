//checked - 100%

#include <iostream>
using namespace std;

#define NumberOfMagicNumbers 38
long long unsigned magicNumbers[NumberOfMagicNumbers] = {2, 6, 19, 36, 199, 336, 1999, 3336, 19999, 33336, 199999, 333336, 1999999, 3333336, 19999999, 33333336, 199999999, 333333336, 1999999999, 3333333336, 19999999999, 33333333336, 199999999999, 333333333336, 1999999999999, 3333333333336, 19999999999999, 33333333333336, 199999999999999, 333333333333336, 1999999999999999, 3333333333333336, 19999999999999999, 33333333333333336, 199999999999999999, 333333333333333336, 1999999999999999999, 3333333333333333336};

int Answer(long long unsigned n)
{
    for (int i = 0; i < NumberOfMagicNumbers - 1; i++)
    {
        if (n >= magicNumbers[i] && n < magicNumbers[i + 1])
        {
            return (i + 1) % 2;
        }
    }

    return 0;
}

void Solve()
{
    long long unsigned n;
    cin >> n;
    cout << Answer(n) << endl;
}

int main()
{
    Solve();
    Solve();
    Solve();

    return 0;
}