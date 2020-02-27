//checked - 100%

#include <cstdio>
#include <vector>

using namespace std;
#define MaxNumberOfVertices 100000

int numberOfVertices;
vector<int> adj[MaxNumberOfVertices];

bool visited[MaxNumberOfVertices];

void ClearAdj()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        adj[i].clear();
    }
}

void Input()
{
    scanf("%d", &numberOfVertices);

    int b;
    for (int a = 0; a < numberOfVertices; a++)
    {
        scanf("%d", &b); b--;
        if (a == b)
        {
            continue;
        }
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

void DFS(int x)
{
    visited[x] = true;

    for (int i = 0; i < adj[x].size(); i++)
    {
        int child = adj[x][i];
        if (!visited[child])
        {
            DFS(child);
        }
    }
}

int GetNumberOfComponents()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        visited[i] = false;
    }

    int numberOfComponents = 0;
    for (int i = 0; i < numberOfVertices; i++)
    {
        if (!visited[i])
        {
            numberOfComponents++;
            DFS(i);
        }
    }

    return numberOfComponents;
}

void Solve()
{
    Input();
    printf("%d", GetNumberOfComponents());
}

int main()
{
    Solve();
    ClearAdj();
    printf(" ");
    Solve();
    printf("\n");
    return 0;
}
