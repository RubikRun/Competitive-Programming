//checked - 65%

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
#define MaxNumberOfSheep 500
#define MaxNumberOfHouses 500
#define MaxNumberOfVertices 1002
#define Infinity 10000

struct Point
{
	int x;
	int y;
};

//Input data
Point sheep[MaxNumberOfSheep];
int numberOfSheep;

Point houses[MaxNumberOfHouses];
int numberOfHouses;

int houseSize;

//Weights
double weight[MaxNumberOfSheep][MaxNumberOfHouses];
vector<double> weights;

double distLimit;

//Graph
int capacity[MaxNumberOfVertices][MaxNumberOfVertices];
int flow[MaxNumberOfVertices][MaxNumberOfVertices];
int numberOfVertices;

//Path
int path[MaxNumberOfVertices];
int pathLen;

bool used[MaxNumberOfVertices];

void Input()
{
	scanf("%d %d %d", &numberOfSheep, &numberOfHouses, &houseSize);

	for (int i = 0; i < numberOfSheep; i++)
	{
		scanf("%d %d", &sheep[i].x, &sheep[i].y);
	}

	for (int i = 0; i < numberOfHouses; i++)
	{
		scanf("%d %d", &houses[i].x, &houses[i].y);
	}
}

double GetDist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void FindWeights()
{
	vector<double> nonUniqueWeights;
	for (int i = 0; i < numberOfSheep; i++)
	{
		for (int j = 0; j < numberOfHouses; j++)
		{
			weight[i][j] = GetDist(sheep[i], houses[j]);
			nonUniqueWeights.push_back(weight[i][j]);
		}
	}
	sort(nonUniqueWeights.begin(), nonUniqueWeights.end());
	for (int i = 0; i < nonUniqueWeights.size(); i++)
	{
		if (weights.empty() || weights.back() != nonUniqueWeights[i])
		{
			weights.push_back(nonUniqueWeights[i]);
		}
	}
}

void ConstructGraph()
{
	numberOfVertices = numberOfSheep + numberOfHouses + 2;

	for (int i = 0; i < numberOfVertices; i++)
	{
		for (int j = 0; j < numberOfVertices; j++)
		{
			capacity[i][j] = 0;
			flow[i][j] = 0;
		}
	}

	for (int i = 1; i <= numberOfSheep; i++)
	{
		capacity[0][i] = 1;
		capacity[i][0] = 1;
	}

	for (int i = 1; i <= numberOfSheep; i++)
	{
		for (int j = numberOfSheep + 1; j < numberOfVertices - 1; j++)
		{
			capacity[i][j] = 1;
			capacity[j][i] = 1;
		}
	}

	for (int i = numberOfSheep + 1; i < numberOfVertices - 1; i++)
	{
		capacity[i][numberOfVertices - 1] = houseSize;
		capacity[numberOfVertices - 1][i] = houseSize;
	}
}

void InitPath()
{
	pathLen = 0;
	for (int i = 0; i < numberOfVertices; i++)
	{
		used[i] = false;
	}
}

bool FindPath(int x)
{
	used[x] = true;
	path[pathLen++] = x;

	if (x == numberOfVertices - 1)
	{
		return true;
	}

	if (x == 0)
	{
		for (int i = 1; i <= numberOfSheep; i++)
		{
			if (!used[i] && capacity[x][i] > 0)
			{
				if (FindPath(i))
				{
					return true;
				}
			}
		}
	}
	else if (x <= numberOfSheep)
	{
		for (int i = numberOfSheep + 1; i < numberOfVertices - 1; i++)
		{
			if (!used[i] && capacity[x][i] > 0 && weight[x - 1][i - numberOfSheep - 1] <= distLimit)
			{
				if (FindPath(i))
				{
					return true;
				}
			}
		}
	}
	else
	{
		if (capacity[x][numberOfVertices - 1] > 0)
		{
			if (FindPath(numberOfVertices - 1))
			{
				return true;
			}
		}

		for (int i = 1; i <= numberOfSheep; i++)
		{
			if (!used[i] && capacity[x][i] > 0 && weight[x - numberOfSheep - 1][i - 1] <= distLimit)
			{
				if (FindPath(i))
				{
					return true;
				}
			}
		}
	}

	used[x] = false;
	pathLen--;

	return false;
}

int GetMaxFlow()
{
	InitPath();
	while (FindPath(0))
	{
		int minCapacity = Infinity;
		for (int i = 0; i < pathLen - 1; i++)
		{
			minCapacity = min(minCapacity, capacity[path[i]][path[i + 1]]);
		}

		for (int i = 0; i < pathLen - 1; i++)
		{
			int p1 = path[i], p2 = path[i + 1];

			flow[p1][p2] += minCapacity;
			capacity[p1][p2] -= minCapacity;
			flow[p2][p1] -= minCapacity;
			capacity[p2][p1] += minCapacity;
		}

		InitPath();
	}

	int maxFlow = 0;
	for (int i = numberOfSheep + 1; i < numberOfVertices - 1; i++)
	{
		maxFlow += flow[i][numberOfVertices - 1];
	}

	return maxFlow;
}

bool Housing()
{
	ConstructGraph();
	return (GetMaxFlow() == numberOfSheep);
}

void FindDistLimit()
{
	distLimit = weights[0];
	if (Housing())
	{
		return;
	}

	int first = 1, last = weights.size() - 1;
	while (first <= last)
	{
		int mid = (first + last) / 2;

		distLimit = weights[mid - 1];
		bool A = Housing();
		distLimit = weights[mid];
		bool B = Housing();

		if (!A && B)
		{
			return;
		}

		if (A)
		{
			last = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}
}

int main()
{
	Input();
	FindWeights();

	FindDistLimit();
	printf("%.6lf\n", distLimit);

	return 0;
}