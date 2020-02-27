//checked - 92%

#include <cstdio>
#include <cmath>

using namespace std;

const double PI = 3.14159265359;

int main()
{
	long long unsigned R, d, n;
	scanf("%llu %llu %llu", &R, &d, &n);

	if (d >= 2 * R)
	{
		printf("%llu\n",(long long unsigned)(n * (n - 1) / (double)2));
	}
	else
	{
		printf("%llu\n", n * (long long unsigned)(n * asin((double)d / (double)2 / (double)R) / PI));
	}

	return 0;
}
