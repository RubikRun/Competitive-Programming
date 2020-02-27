//checked - 50%

#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
#define MaxNumberOfNodes 1000
#define Infinity 99999999

vector< pair<int, int> > adj[MaxNumberOfNodes];
int numberOfNodes;

vector<int> leafs;

int dist[MaxNumberOfNodes][MaxNumberOfNodes];

void Input()
{
	scanf("%d", &numberOfNodes);

	int a, b, w;
	for (int i = 0; i < numberOfNodes - 1; i++)
	{
		scanf("%d %d %d", &a, &b, &w);
		a--; b--;

		adj[a].push_back({b, w});
		adj[b].push_back({a, w});
	}
}

void FindLeafs()
{
	for (int i = 0; i < numberOfNodes; i++)
	{
		if (adj[i].size() == 1)
		{
			leafs.push_back(i);
		}
	}
}

void BFS(int root)
{
	bool used[MaxNumberOfNodes];
	for (int i = 0; i < numberOfNodes; i++)
	{
		used[i] = false;
	}
	used[root] = true;
	dist[root][root] = 0;

	queue<int> q;
	q.push(root);
	while (!q.empty())
	{
		int a = q.front();
		q.pop();

		for (int i = 0; i < adj[a].size(); i++)
		{
			int b = adj[a][i].first, w = adj[a][i].second;

			if (!used[b])
			{
				dist[root][b] = dist[root][a] + w;
				dist[b][root] = dist[root][a] + w;
				used[b] = true;
				q.push(b);
			}
		}
	}
}

void FillDistFromAllLeafs()
{
	for (int i = 0; i < leafs.size(); i++)
	{
		BFS(leafs[i]);
	}
}

int GetPhi(int x)
{
	int minDist = Infinity, maxDist = 0;

	for (int i = 0; i < leafs.size(); i++)
	{
		if (leafs[i] == x)
		{
			continue;
		}
		minDist = min(minDist, dist[x][leafs[i]]);
		maxDist = max(maxDist, dist[x][leafs[i]]);
	}

	return maxDist - minDist;
}

pair<int, int> GetBestNodeAndItsPhi()
{
	pair<int, int> result = {-1, Infinity};

	for (int i = 0; i < numberOfNodes; i++)
	{
		int phi = GetPhi(i);
		if (phi < result.second)
		{
			result = {i, phi};
		}
	}

	return result;
}

int main()
{
	Input();

	FindLeafs();
	FillDistFromAllLeafs();
	pair<int, int> answer = GetBestNodeAndItsPhi();

	printf("%d %d\n", answer.first + 1, answer.second);

	return 0;
}