//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MAXN 1500

int dp[MAXN], n;

int main()
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a;
			scanf("%d", &a);
			if (i == 0 && j == 0)
			{
				dp[j] = 1;
				continue;
			}

			int up = dp[j];
			dp[j] = 9999999;
			if (j - 1 >= 0) dp[j] = min(dp[j], dp[j - 1] + 1 + (dp[j - 1] % 2 != a % 2));
			if (i - 1 >= 0) dp[j] = min(dp[j], up + 1 + (up % 2 != a % 2));
		}
	}

	printf("%d\n", dp[n - 1]);

	return 0;
}
