//checked - 100%

#include <cstdio>

using namespace std;

#define MAXN 800
#define NoValue -1

long long ways[MAXN + 1][MAXN + 1];

void InitWays(int n, int k)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            ways[i][j] = NoValue;
        }
    }
}

long long GetWays(int n, int k)
{
    if (n < k)
    {
        return 0;
    }
    if (n == k || k == 1)
    {
        return 1;
    }

    if (ways[n][k] != NoValue)
    {
        return ways[n][k];
    }

    ways[n][k] = GetWays(n - 1, k - 1) + GetWays(n - k, k);
    return ways[n][k];
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    InitWays(n, k);
    printf("%lld\n", GetWays(n, k));

    return 0;
}