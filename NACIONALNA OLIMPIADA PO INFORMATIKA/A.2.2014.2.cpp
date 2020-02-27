//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 99999
#define MAXP 9
#define MinusInfinity -2147483648

int main()
{
	int n, b, c, d;
	scanf("%d %d %d %d", &n, &b, &c, &d);

	int a[MAXN];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	int t[MAXN][MAXP + 1];
	for (int i = b; i <= c; i++)
	{
		t[0][i] = a[0] * i;
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = b; j <= c; j++)
		{
			t[i][j] = MinusInfinity;
			for (int k = max(b, j - d); k <= min(c, j + d); k++)
			{
				t[i][j] = max(t[i][j], t[i - 1][k] + a[i] * j);
			}
		}
	}

	int s = MinusInfinity;
	for (int i = b; i <= c; i++)
	{
		s = max(s, t[n - 1][i]);
	}

	printf("%d\n", s);

	return 0;
}
