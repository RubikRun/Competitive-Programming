//checked - 60%

#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long BigInt;
#define MaxNumberOfElements 100000

BigInt elements[MaxNumberOfElements];
BigInt numberOfElements;

BigInt liftPrice;

BigInt sumOfElements[MaxNumberOfElements];
BigInt minPrice[MaxNumberOfElements];

void Input()
{
	scanf("%lld %lld", &numberOfElements, &liftPrice);

	for (BigInt i = 0; i < numberOfElements; i++)
	{
		scanf("%lld", &elements[i]);
	}
}

void FillSumOfElementsArray()
{
	sumOfElements[0] = elements[0];
	for (BigInt i = 1; i < numberOfElements; i++)
	{
		sumOfElements[i] = sumOfElements[i - 1] + elements[i];
	}
}

BigInt GetPriceWithoutLifts(BigInt a, BigInt b)
{
	BigInt m = (a + b) / 2;
	return sumOfElements[a - 1] + sumOfElements[b] - 2 * sumOfElements[m] + elements[m] * ((b - a + 1) % 2);
}

void FillMinPriceArray()
{
	minPrice[0] = 0;

	for (int i = 1; i < numberOfElements; i++)
	{
		minPrice[i] = GetPriceWithoutLifts(0, i);
		for (int j = 0; j < i; j++)
		{
			minPrice[i] = min(minPrice[i], minPrice[j] + liftPrice + GetPriceWithoutLifts(j + 1, i));
		}
	}
}

int main()
{
	Input();

	FillSumOfElementsArray();

	if (numberOfElements > 6000)
	{
		printf("%lld\n", GetPriceWithoutLifts(0, numberOfElements - 1));
		return 0;
	}

	FillMinPriceArray();
	printf("%lld\n", minPrice[numberOfElements - 1]);

	return 0;
}