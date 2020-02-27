#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define MaxNumberOfVertices 100000

ifstream Read ("maxpath.in");
ofstream Write ("maxpath.out");

vector<int> adj[MaxNumberOfVertices];
int numberOfVertices;

bool used[MaxNumberOfVertices];

void Input()
{
	int numberOfEdges;
	Read >> numberOfVertices >> numberOfEdges;

	int a, b;
	for (int i = 0; i < numberOfEdges; i++)
	{
		Read >> a >> b;
		a--; b--;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}

vector<int> GetGreedyPath(int root)
{
	for (int i = 0; i < numberOfVertices; i++) used[i] = false;

	vector<int> greedyPath = {root};
	used[root] = true;

	int a = -1, b = root;
	do
	{
		int y = -1;
		for (int i = 0; i < adj[b].size(); i++)
		{
			if (adj[b][i] == a || used[adj[b][i]]) continue;
			y = max(y, adj[b][i]);
		}

		if (y == -1) break;
		greedyPath.push_back(y);
		used[y] = true;
		a = b;
		b = y;
	} while (adj[b].size() > 1);

	reverse(greedyPath.begin(), greedyPath.end());
	return greedyPath;
}

int GetPathValue(vector<int> path)
{
	int value = 0;
	for (int i = 0; i < path.size(); i++)
	{
		value += (i + 1) * (path[i] + 1);
	}
	return value;
}

vector<int> GetMaxPath()
{
	vector<int> maxPath;

	for (int i = max(0, numberOfVertices - 1000); i < numberOfVertices; i++)
	{
		vector<int> greedyPath = GetGreedyPath(i);
		if (GetPathValue(greedyPath) > GetPathValue(maxPath))
		{
			maxPath = greedyPath;
		}
	}

	return maxPath;
}

int main()
{
	Input();

	vector<int> maxPath = GetMaxPath();
	Write << maxPath.size() << endl;
	for (int i = 0; i < maxPath.size(); i++)
	{
		Write << maxPath[i] + 1 << endl;
	}

	return 0;
}