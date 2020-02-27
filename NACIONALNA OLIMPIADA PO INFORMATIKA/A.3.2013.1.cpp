//checked - 90%

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;
#define MaxNumberOfRows 30
#define MaxNumberOfCols 30
#define MaxNumberOfCells MaxNumberOfRows * MaxNumberOfCols
#define MaxNumberOfVertices 2 * MaxNumberOfRows * MaxNumberOfCols + 2

int tab[MaxNumberOfRows][MaxNumberOfCols];
int numberOfRows, numberOfCols;

vector<int> innerOnes;
vector<int> outerZeros;
int numberOfCells;

vector<int> children[MaxNumberOfVertices];
vector<int> parents[MaxNumberOfVertices];
int numberOfVertices;
int source, sink;

int flow[MaxNumberOfVertices][MaxNumberOfVertices];
int capacity[MaxNumberOfVertices][MaxNumberOfVertices];

bool used[MaxNumberOfVertices];
vector<int> path;

void Input()
{
	scanf("%d", &numberOfRows);

	for (int i = 0; i < numberOfRows; i++)
	{
		char inputLine[MaxNumberOfCols + 1];
		scanf("%s", inputLine);

		numberOfCols = strlen(inputLine);
		for (int j = 0; j < numberOfCols; j++)
		{
			tab[i][j] = inputLine[j] - '0';
		}
	}
}

bool IsOuterCell(int cell)
{
	int row = cell / numberOfCols;
	int col = cell % numberOfCols;
	return (col == 0 || col == numberOfCols - 1 || row == 0 || row == numberOfRows - 1);
}

void TraverseCells()
{
	numberOfCells = numberOfRows * numberOfCols;
	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < numberOfCols; j++)
		{
			int cell = i * numberOfCols + j;

			if (IsOuterCell(cell))
			{
				if (tab[i][j] == 0)
				{
					outerZeros.push_back(cell);
				}
			}
			else
			{
				if (tab[i][j] == 1)
				{
					innerOnes.push_back(cell);
				}
			}
		}
	}
}

void AddEdge(int a, int b)
{
	children[a].push_back(b);
	parents[b].push_back(a);
}

void ConstructGraph()
{
	numberOfVertices = 2 * numberOfCells + 2;
	source = 2 * numberOfCells;
	sink = 2 * numberOfCells + 1;

	for (int i = 0; i < numberOfCells; i++)
	{
		int row = i / numberOfCols;
		int col = i % numberOfCols;

		if (row - 1 >= 0 && tab[row - 1][col] == 0)
		{
			int j = (row - 1) * numberOfCols + col;
			AddEdge(numberOfCells + i, j);
		}
		if (row + 1 < numberOfRows && tab[row + 1][col] == 0)
		{
			int j = (row + 1) * numberOfCols + col;
			AddEdge(numberOfCells + i, j);
		}
		if (col - 1 >= 0 && tab[row][col - 1] == 0)
		{
			int j = row * numberOfCols + col - 1;
			AddEdge(numberOfCells + i, j);
		}
		if (col + 1 < numberOfCols && tab[row][col + 1] == 0)
		{
			int j = row * numberOfCols + col + 1;
			AddEdge(numberOfCells + i, j);
		}
	}

	for (int i = 0; i < numberOfCells; i++)
	{
		AddEdge(i, numberOfCells + i);
	}

	for (int i = 0; i < innerOnes.size(); i++)
	{
		AddEdge(source, innerOnes[i]);
	}

	for (int i = 0; i < outerZeros.size(); i++)
	{
		AddEdge(numberOfCells + outerZeros[i], sink);
	}
}

void InitFlowAndCapacity()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		for (int j = 0; j < numberOfVertices; j++)
		{
			flow[i][j] = 0;
			capacity[i][j] = 0;
		}
	}

	for (int i = 0; i < numberOfVertices; i++)
	{
		for (int j = 0; j < children[i].size(); j++)
		{
			capacity[i][children[i][j]] = 1;
		}
	}
}

bool FindAugmentingPath(int x)
{
	path.push_back(x);
	used[x] = true;

	if (x == sink)
	{
		return true;
	}

	for (int i = 0; i < children[x].size(); i++)
	{
		int child = children[x][i];
		if (!used[child] && capacity[x][child] > 0 && FindAugmentingPath(child))
		{
			return true;
		}
	}
	for (int i = 0; i < parents[x].size(); i++)
	{
		int parent = parents[x][i];
		if (!used[parent] && capacity[x][parent] > 0 && FindAugmentingPath(parent))
		{
			return true;
		}
	}

	used[x] = false;
	path.pop_back();

	return false;
}

void InitUsed()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		used[i] = false;
	}
}

int GetMaxFlow()
{
	InitFlowAndCapacity();
	InitUsed();

	while (FindAugmentingPath(source))
	{
		for (int i = 0; i < path.size() - 1; i++)
		{
			int p1 = path[i], p2 = path[i + 1];

			flow[p1][p2]++;
			flow[p2][p1]--;
			capacity[p1][p2]--;
			capacity[p2][p1]++;
		}

		InitUsed();
		path.clear();
	}

	int maxFlow = 0;
	for (int i = 0; i < children[source].size(); i++)
	{
		maxFlow += flow[source][children[source][i]];
	}

	return maxFlow;
}

int main()
{
	Input();

	if (numberOfRows == 1 && numberOfCols == 1)
	{
		printf("%d\n", tab[0][0]);
		return 0;
	}
	if (numberOfRows == 1)
	{
		int numberOfCats = 0;
		for (int i = 0; i < numberOfCols; i++) numberOfCats += tab[0][i];
		printf("%d\n", numberOfCats);
		return 0;
	}
	if (numberOfCols == 1)
	{
		int numberOfCats = 0;
		for (int i = 0; i < numberOfRows; i++) numberOfCats += tab[i][0];
		printf("%d\n", numberOfCats);
		return 0;
	}

	TraverseCells();
	ConstructGraph();

	int maxFlow = GetMaxFlow();
	int numberOfOuterOnes = 2 * numberOfRows + 2 * numberOfCols - 4 - outerZeros.size();

	printf("%d\n", maxFlow + numberOfOuterOnes);

	return 0;
}

