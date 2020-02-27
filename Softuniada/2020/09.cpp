#include <iostream>
using namespace std;

#define COINSNEEDED 23
#define MAXP 1000000

int dp[MAXP];

int main()
{
    long long coins[COINSNEEDED] = {1, 10,
    25, 100, 1000, 
    2500, 10000, 100000, 
    250000, 1000000, 10000000, 
    25000000, 100000000, 1000000000, 
    2500000000, 10000000000, 100000000000, 
    250000000000, 1000000000000, 10000000000000, 
    25000000000000, 100000000000000, 1000000000000000};
    long long p;
    cin >> p;

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= p; i++)
    {
        dp[i] = MAXP;
        for (int j = 0; coins[j] <= i; j++)
        {
            dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
    }
    cout << dp[p] << endl;

    return 0;
}