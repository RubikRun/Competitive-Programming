#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
#define MaxNumberOfNodes 1000005
#define TravelPowerLimit 23

struct Edge
{
	long long endVertex;
	long long weight;
};

Edge parent[MaxNumberOfNodes];
vector<Edge> children[MaxNumberOfNodes];
long long numberOfNodes;

long long travelUp[MaxNumberOfNodes][TravelPowerLimit];
long long maxTravelPower;

long long depth[MaxNumberOfNodes];
long long distFromRoot[MaxNumberOfNodes];

long long ANC;

void Input()
{
	parent[0] = {-1, -1};

	scanf("%lld", &numberOfNodes);

	for (long long i = 1; i < numberOfNodes; i++)
	{
		long long p, w;
		scanf("%lld %lld", &p, &w);
		parent[i] = {p - 1, w};
		children[parent[i].endVertex].push_back({i, w});
	}
}

void FindMaxTravelPower()
{
	maxTravelPower = 0;
	long long t = 1;
	while (t * 2 < numberOfNodes)
	{
		t *= 2;
		maxTravelPower++;
	}
}

void FindDepthsAndDistsFromRoot()
{
	queue<int> q;
	q.push(0);
	depth[0] = 0;
	distFromRoot[0] = 0;

	while (!q.empty())
	{
		long long a = q.front();
		q.pop();

		for (long long i = 0; i < children[a].size(); i++)
		{
			long long b = children[a][i].endVertex, w = children[a][i].weight;
			depth[b] = depth[a] + 1;
			distFromRoot[b] = distFromRoot[a] + w;
			q.push(b);
		}
	}
}

void FindTravelUps()
{
	for (long long i = 0; i < numberOfNodes; i++)
	{
		travelUp[i][0] = parent[i].endVertex;
	}

	for (long long travelPower = 1; travelPower <= maxTravelPower; travelPower++)
	{
		for (long long i = 0; i < numberOfNodes; i++)
		{
			travelUp[i][travelPower] = travelUp[travelUp[i][travelPower - 1]][travelPower - 1];
		}
	}
}

long long GetLowestCommonAncestor(long long a, long long b)
{
	if (depth[a] != depth[b])
	{
		if (depth[a] > depth[b])
		{
			long long t = a;
			a = b;
			b = t;
		}

		long long deltaLeft = depth[b] - depth[a];

		long long travelPower = maxTravelPower;
		long long travelSize = 1 << travelPower;
		while (deltaLeft > 0)
		{
			while (travelSize > deltaLeft)
			{
				travelPower--;
				travelSize >>= 1;
			}
			deltaLeft -= travelSize;
			b = travelUp[b][travelPower];
		}
	}

	if (a == b)
	{
		return a;
	}

	long long travelPower = maxTravelPower;
	long long travelSize = 1 << travelPower;
	while (travelUp[a][0] != travelUp[b][0])
	{
		while (travelUp[a][travelPower] == travelUp[b][travelPower])
		{
			travelPower--;
			travelSize >>= 1;
		}
		a = travelUp[a][travelPower];
		b = travelUp[b][travelPower];
		if (a == b)
		{
			return -1;
		}
	}

	return travelUp[a][0];
}

long long GetDist(long long a, long long b)
{
	ANC = GetLowestCommonAncestor(a, b);
	return distFromRoot[a] + distFromRoot[b] - 2 * distFromRoot[ANC];
}

long long AnswerQuery(long long a, long long b, long long t)
{
	long long RtoA = distFromRoot[a];
	long long AtoB = GetDist(a, b);
	long long RtoANC = distFromRoot[ANC];
	long long ANCtoB = distFromRoot[b] - distFromRoot[ANC];

	long long result = RtoANC + 2 * t + ANCtoB;
	if (RtoA > AtoB)
	{
		result = min(result, RtoA + AtoB);
		result = min(result, t + AtoB);
	}
	else
	{
		result = min(result, RtoA + AtoB);
		result = min(result, RtoA + t);
	}
	return result;
}

int main()
{
	Input();

	FindDepthsAndDistsFromRoot();
	FindMaxTravelPower();
	FindTravelUps();

	long long numberOfQueries;
	scanf("%lld", &numberOfQueries);
	for (long long i = 0; i < numberOfQueries; i++)
	{
		long long a, b, t;
		scanf("%lld %lld %lld", &a, &b, &t);
		a--;
		b--;

		printf("%lld\n", AnswerQuery(a, b, t));
	}

	return 0;
}