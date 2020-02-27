/*
ID: borisd22
TASK: kimbits
LANG: C++
*/

#include <fstream>

using namespace std;
#define Read fin
#define Write fout
#define MAXN 32
#define NotFound -1

ifstream fin ("kimbits.in");
ofstream fout ("kimbits.out");

long long count[MAXN][MAXN];

void InitCount(int n)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            count[i][j] = NotFound;
        }
    }
}

long long GetCount(long long n, long long l)
{
    if (count[n][l] != NotFound)
    {
        return count[n][l];
    }

    if (l >= n)
    {
        return 1 << n;
    }

    if (l < 1)
    {
        return 1;
    }
    if (n == 1)
    {
        return 2;
    }

    return GetCount(n - 1, l) + GetCount(n - 1, l - 1);
}

void Make(long long n, long long l, long long x)
{
    if (n == 1)
    {
        Write << x - 1;
        return;
    }
    if (GetCount(n - 1, l) < x)
    {
        Write << 1;
        Make(n - 1, l - 1, x - GetCount(n - 1, l));
    }
    else
    {
        Write << 0;
        Make(n - 1, l, x);
    }
}

int main()
{
    long long n, l, x;
    Read >> n >> l >> x;

    InitCount(n);
    Make(n, l, x);
    Write << endl;

    return 0;
}
