//checked - 100%

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
#define MaxNumberOfNodes 100000

struct Node
{
	int level;
	int child;
	int numberOfParents;

	bool operator<(const Node& a) const
	{
		return (level < a.level);
	}
};

Node nodes[MaxNumberOfNodes];
int numberOfNodes;

int numberOfMachines;

priority_queue<Node> leafs;

void Input()
{
	scanf("%d %d", &numberOfNodes, &numberOfMachines);

	for (int i = 0; i < numberOfNodes; i++)
	{
		nodes[i] = {-1, -1, 0};
	}

	vector<int> parents[MaxNumberOfNodes];
	int parent, child;
	for (int i = 0; i < numberOfNodes - 1; i++)
	{
		scanf("%d %d", &parent, &child); parent--; child--;
		nodes[parent].child = child;
		nodes[child].numberOfParents++;
		parents[child].push_back(parent);
	}

	int root = 0;
	while (nodes[root].child != -1)
	{
		root = nodes[root].child;
	}
	nodes[root].level = 0;

	queue<int> q;
	q.push(root);
	while (!q.empty())
	{
		int currNode = q.front();
		q.pop();

		if (parents[currNode].empty())
		{
			leafs.push(nodes[currNode]);
		}
		for (int i = 0; i < parents[currNode].size(); i++)
		{
			int currParent = parents[currNode][i];
			nodes[currParent].level = nodes[currNode].level + 1;
			q.push(currParent);
		}
	}
}

bool TactPass()
{
	if (leafs.empty())
	{
		return false;
	}

	vector<Node> newLeafs;
	for (int i = 0; i < numberOfMachines && !leafs.empty(); i++)
	{
		Node currLeaf = leafs.top();
		leafs.pop();

		Node* currChild = &nodes[currLeaf.child];
		currChild->numberOfParents--;
		if (currChild->numberOfParents == 0)
		{
			newLeafs.push_back(*currChild);
		}
	}

	for (int i = 0; i < newLeafs.size(); i++)
	{
		leafs.push(newLeafs[i]);
	}

	return true;
}

int GetNumberOfTacts()
{
	for (int i = 0; true; i++)
	{
		if (!TactPass())
		{
			return i;
		}
	}

	return -1;
}

int main()
{
	Input();
	printf("%d\n", GetNumberOfTacts());

	return 0;
}
