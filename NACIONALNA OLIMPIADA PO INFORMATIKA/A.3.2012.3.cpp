//checked - 100%

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long BigInt;

BigInt d;

void SolveDiophantineEquation(BigInt a, BigInt b, BigInt c, BigInt& x, BigInt& y)
{
	vector<BigInt> g = {a, b};
	BigInt l1 = a, l2 = b;
	while (g.back() != 0)
	{
		g.push_back(l1 % l2);
		l1 = l2;
		l2 = g.back();
	}
	g.pop_back();

	d = g.back();
	if (c % d != 0)
	{
		x = 0;
		y = 0;
		return;
	}
	BigInt dd = c / d;

	vector<pair<BigInt, BigInt>> v = {{1, 0}, {0, 1}};
	for (int i = 2; i < g.size(); i++)
	{
		BigInt k = g[i - 2] / g[i - 1];
		v.push_back({v[i - 2].first - k * v[i - 1].first, v[i - 2].second - k * v[i - 1].second});
	}

	x = v.back().first * dd;
	y = v.back().second * dd;
}

int main()
{
	BigInt a, b, c, m, n;
	scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &m, &n);

	BigInt a1 = c - a, b1 = c - b, c1 = m * c - n;
	BigInt xx, yy;
	SolveDiophantineEquation(a1, b1, c1, xx, yy);
	if (xx == 0 && yy == 0)
	{
		printf("0\n");
		return 0;
	}

	BigInt v1 = ceil((double)(-xx * d) / (b1));
	BigInt v2 = floor((double)(yy * d) / (a1));
	BigInt v3 = ceil((double)(-d * (m - xx - yy)) / (a1 - b1));

	BigInt p = max(v1, v3);
	BigInt q = v2;

	printf("%lld\n", q - p + 1);

	return 0;
}

