#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MaxDogLen 10000

bool isPal[MaxDogLen][MaxDogLen];

int main()
{
	char dog[MaxDogLen];
	scanf("%s", dog);
	int dogLen = strlen(dog);

	for (int palLen = 1; palLen <= dogLen; palLen++)
	{
		for (int first = 0; first + palLen - 1 < dogLen; first++)
		{
			int last = first + palLen - 1;
			
			isPal[first][last] = false;
			if (dog[first] == dog[last])
			{
				isPal[first][last] = true;
				if (first + 1 <= last - 1 && !isPal[first + 1][last - 1])
				{
					isPal[first][last] = false;
				}
			}
		}
	}

	int minCut[MaxDogLen];
	minCut[0] = 0;
	for (int i = 1; i < dogLen; i++)
	{
		if (isPal[0][i])
		{
			minCut[i] = 0;
			continue;
		}

		minCut[i] = minCut[i - 1] + 1;
		for (int j = i - 1; j > 0; j--)
		{
			if (isPal[j][i])
			{
				minCut[i] = min(minCut[i], minCut[j - 1] + 1);
			}
		}
	}

	printf("%d\n", minCut[dogLen - 1]);

	return 0;
}
