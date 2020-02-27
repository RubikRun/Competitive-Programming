#include <iostream>
#include <cstring>
using namespace std;

#define COINVALUES 3
#define MAXPLEN 17

int coinValues[COINVALUES] = {1, 10, 25};

int DoDP(int x)
{
    int dp[100] = {0, 1};
    for (int i = 2; i <= x; i++)
    {
        dp[i] = 100;
        for (int j = 0; coinValues[j] <= i; j++)
        {
            dp[i] = min(dp[i], dp[i - coinValues[j]] + 1);
        }
    }
    return dp[x];
}

int main()
{
    long long n;
    cin >> n;

    int d[MAXPLEN];
    int dLen = 0;
    while (n > 0)
    {
        d[dLen++] = n % 10;
        n /= 10;
    }
    for (int i = 0; i <= dLen / 2; i++)
    {
        int t = d[i];
        d[i] = d[dLen - 1 - i];
        d[dLen - 1 - i] = t;
    }

    int x = 0;
    if (dLen % 2 == 0)
    {
        for (int i = 0; i < dLen; i += 2)
        {
            x += DoDP(d[i] * 10 + d[i + 1]);
        }
    }
    else
    {
        for (int i = 0; i < dLen - 3; i += 2)
        {
            x += DoDP(d[i] * 10 + d[i + 1]);
        }
        x += min(DoDP(d[dLen - 3] * 10 + d[dLen - 2]) + d[dLen - 1], d[dLen - 3] + DoDP(d[dLen - 2] * 10 + d[dLen - 1]));
    }
    cout << x << endl;

    return 0;
}