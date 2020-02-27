//checked - 10%

#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;
#define MaxNumberOfRows 30000
#define MaxNumberOfCols 30000

int left[MaxNumberOfRows];
int right[MaxNumberOfRows];
int up[MaxNumberOfCols];
int down[MaxNumberOfCols];

int numberOfRows, numberOfCols;

set<pair<int, int>> dirtySquares;

void Input()
{
	int numberOfRobots;
	scanf("%d %d %d", &numberOfRobots, &numberOfRows, &numberOfCols);

	for (int i = 0; i < numberOfRows; i++)
	{
		left[i] = numberOfCols;
		right[i] = -1;
	}
	for (int i = 0; i < numberOfCols; i++)
	{
		up[i] = numberOfRows;
		down[i] = -1;
	}

	int row, col;
	char dir;
	for (int i = 0; i < numberOfRobots; i++)
	{
		scanf("%d %d %c", &row, &col, &dir);
		row--; col--;

		switch(dir)
		{
			case 'r': left[row] = min(left[row], col); break;
			case 'l': right[row] = max(right[row], col); break;
			case 'd': up[col] = min(up[col], row); break;
			case 'u': down[col] = max(down[col], row); break;
		}
	}
}

void FindDirtySquares()
{
	for (int i = 0; i < numberOfRows; i++)
	{
		if (left[i] <= right[i])
		{
			for (int j = 0; j < numberOfCols; j++)
			{
				dirtySquares.insert({i, j});
			}
			continue;
		}

		for (int j = left[i]; j < numberOfCols; j++)
		{
			dirtySquares.insert({i, j});
		}
		for (int j = 0; j <= right[i]; j++)
		{
			dirtySquares.insert({i, j});
		}
	}

	for (int j = 0; j < numberOfCols; j++)
	{
		if (up[j] <= down[j])
		{
			for (int i = 0; i < numberOfRows; i++)
			{
				dirtySquares.insert({i, j});
			}
			continue;
		}

		for (int i = up[j]; i < numberOfRows; i++)
		{
			dirtySquares.insert({i, j});
		}
		for (int i = 0; i <= down[j]; i++)
		{
			dirtySquares.insert({i, j});
		}
	}
}

int main()
{
	Input();

	FindDirtySquares();
	printf("%lu\n", dirtySquares.size());

	return 0;
}