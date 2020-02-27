#include <cstdio>
using namespace std;

int main()
{
	int b, k;
	scanf("%d %d", &b, &k);

	int t = 0, a;
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &a);
		if (a % 2 != 0) t++;
	}

	bool even;
	if (b % 2 == 0)
	{
		even = (a % 2 == 0);
	}
	else
	{
		even = (t % 2 == 0);
	}

	if (even)
	{
		printf("even\n");
	}
	else
	{
		printf("odd\n");
	}

	return 0;
}