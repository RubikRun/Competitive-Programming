/*
ID: borisd22
PROG: fact4
LANG: C++
*/

#include <fstream>

using namespace std;
#define MOD 100000

ifstream fin("fact4.in");
ofstream fout("fact4.out");

int main()
{
    int n;
    fin >> n;

    int d = 1;
    for (int i = 2; i <= n; i++)
    {
        d = d * i % MOD;
        while (d % 10 == 0)
        {
            d /= 10;
        }
    }

    fout << d % 10 << endl;

    return 0;
}
