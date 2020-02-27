//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MAXN 10000000
typedef long long ll;

int sequence[MAXN];
int prevMax[MAXN];
int nextMax[MAXN];

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);

	ll first, mul, add, mod;
	scanf("%lld %lld %lld %lld", &first, &mul, &add, &mod);

	sequence[0] = (int)first;
	for (int i = 1; i < n; i++)
	{
		sequence[i] = (sequence[i - 1] * mul + add) % mod;
	}

	for (int i = 0; i < n; i++)
	{
		if (i % k == 0)
		{
			prevMax[i] = -1;
		}
		else
		{
			prevMax[i] = max(prevMax[i - 1], sequence[i - 1]);
		}
	}

	for (int i = n - 1; i >= 0; i--)
	{
		if (i % k == k - 1)
		{
			nextMax[i] = -1;
		}
		else
		{
			nextMax[i] = max(nextMax[i + 1], sequence[i + 1]);
		}
	}

	ll sum = 0;
	for (int i = 0; i < n; i++)
	{
		ll curr = sequence[i];
		if (prevMax[i] > curr)
		{
			curr = prevMax[i];
		}
		if (i - k >= 0 && nextMax[i - k] > curr)
		{
			curr = nextMax[i - k];
		}
		sum += curr;
	}

	printf("%lld\n", sum);

	return 0;
}
