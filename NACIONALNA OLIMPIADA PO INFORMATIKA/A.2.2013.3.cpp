//correctness - 100%
//speed - 90%

#include <iostream>
using namespace std;

#define MaxNumberOfDigits 15

long long tenthPower[MaxNumberOfDigits + 1] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000};

long long GetPal(long long block, int odd)
{
	long long pal = block;
	if (odd)
	{
		block /= 10;
	}

	while (block != 0)
	{
		pal *= 10;
		pal += block % 10;
		block /= 10;
	}

	return pal;
}

void PalSolution(int n, int p)
{
	long long firstBlock = tenthPower[(n + 1) / 2 - 1];
	long long lastBlock = firstBlock * 10 - 1;

	long long numberOfPals = 0;
	long long pal;
	for (long long block = firstBlock; block <= lastBlock; block++)
	{
		pal = GetPal(block, n % 2);
		if (pal % p == 0)
		{
			numberOfPals++;
		}
	}

	printf("%lld\n", numberOfPals);
}

bool IsPal(long long x)
{
	long long xt = x;
	long long y = 0;

	while (xt != 0)
	{
		y *= 10;
		y += xt % 10;
		xt /= 10;
	}

	return (x == y);
}

void DivSolution(int n, int p)
{
	long long multiple = tenthPower[n - 1];
	while (multiple % p != 0)
	{
		multiple++;
	}
	
	long long numberOfPals = 0;
	while (multiple < tenthPower[n])
	{
		if (IsPal(multiple))
		{
			numberOfPals++;
		}
		multiple += p;
	}

	printf("%lld\n", numberOfPals);
}



int main()
{
	int n, p;
	cin >> n >> p;

	if (p % 10 == 0)
	{
		printf("0\n");
		return 0;
	}

	long long palComplexity = 9 * tenthPower[n / 2 - (n % 2 == 0)];
	long long divComplexity = 9 * tenthPower[n - 1] / p;

	if (palComplexity < divComplexity)
	{
		PalSolution(n, p);
	}
	else
	{
		DivSolution(n, p);
	}

	return 0;
}
