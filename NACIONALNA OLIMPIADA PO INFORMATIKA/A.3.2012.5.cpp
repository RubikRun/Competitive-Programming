//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MAXN 1000

int a[MAXN];
int dp[MAXN][MAXN];
int n;

int k;

int phi(int x, int y)
{
	if (x <= y)
	{
		return y - x;
	}
	return k + y - x;
}

int main()
{
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	for (int i = 0; i < k; i++)
	{
		dp[0][i] = -1;
	}
	dp[0][0] = 0;
	dp[0][a[0] % k] = 1;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			dp[i][j] = dp[i - 1][j];
			int r = phi(a[i] % k, j);
			if (dp[i - 1][r] != -1)
			{
				dp[i][j] = max(dp[i][j], dp[i - 1][r] + 1);
			}
		}
	}

	printf("%d\n", dp[n - 1][0]);

	return 0;
}