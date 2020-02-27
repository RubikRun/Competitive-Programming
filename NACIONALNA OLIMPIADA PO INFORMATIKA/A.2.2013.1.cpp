//checked - 100%

#include <cstdio>
#include <vector>

using namespace std;

#define MaxNumberOfVertices 1000

vector<int> adj[MaxNumberOfVertices];
int numberOfVertices;

int parent[MaxNumberOfVertices];

void Input()
{
    scanf("%d", &numberOfVertices);
    int numberOfEdges;
    scanf("%d", &numberOfEdges);

    int a, b;
    for (int i = 0; i < numberOfEdges; i++)
    {
        scanf("%d %d", &a, &b); a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

void DFS(int currNode, int prevNode, bool visited[])
{
    parent[currNode] = prevNode;
    visited[currNode] = true;

    for (int i = 0; i < adj[currNode].size(); i++)
    {
        int nextNode = adj[currNode][i];

        if (!visited[nextNode])
        {
            DFS(nextNode, currNode, visited);
        }
    }
}

void CreateTrees()
{
    bool visited[MaxNumberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (!visited[i])
        {
            DFS(i, -1, visited);
        }
    }
}

int GetTreeRoot(int node)
{
    while (parent[node] != -1)
    {
        node = parent[node];
    }

    return node;
}

void AddEdge(int a, int b)
{
    for (int i = 0; i < adj[a].size(); i++)
    {
        if (adj[a][i] == b)
        {
            return;
        }
    }
    adj[a].push_back(b);
    adj[b].push_back(a);

    int aRoot = GetTreeRoot(a);
    int bRoot = GetTreeRoot(b);

    if (aRoot == bRoot)
    {
        return;
    }

    parent[aRoot] = bRoot;
}

void RemoveEdge(int a, int b)
{
    bool edgeDidntExist = true;
    for (int i = 0; i < adj[a].size(); i++)
    {
        if (adj[a][i] == b)
        {
            adj[a].erase(adj[a].begin() + i);

            for (int j = 0; j < adj[b].size(); j++)
            {
                if (adj[b][j] == a)
                {
                    adj[b].erase(adj[b].begin() + j);
                    break;
                }
            }

            edgeDidntExist = false;
            break;
        }
    }
    if (edgeDidntExist)
    {
        return;
    }

    bool visited[MaxNumberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        visited[i] = false;
    }
    DFS(a, -1, visited);

    for (int i = 0; i < numberOfVertices; i++)
    {
        visited[i] = false;
    }
    DFS(b, -1, visited);
}

void Query(int code, int a, int b)
{
    if (code == 1)
    {
        int aRoot = GetTreeRoot(a);
        int bRoot = GetTreeRoot(b);

        if (aRoot == bRoot)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    else if (code == 2)
    {
        AddEdge(a, b);
    }
    else
    {
        RemoveEdge(a, b);
    }
}

int main()
{
    Input();
    CreateTrees();

    int numberOfQueries;
    scanf("%d", &numberOfQueries);

    int code, a, b;
    for (int i = 0; i < numberOfQueries; i++)
    {
        scanf("%d %d %d", &code, &a, &b); a--; b--;
        Query(code, a, b);
    }

    return 0;
}