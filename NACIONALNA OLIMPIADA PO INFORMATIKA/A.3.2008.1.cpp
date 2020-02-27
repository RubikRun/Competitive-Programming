//checked - 100%

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
#define MaxNumberOfVertices 999

int numberOfVertices;
vector< pair<int, int> > adj[MaxNumberOfVertices];

void Input()
{
    scanf("%d", &numberOfVertices);

    int a, b, w;
    for (int i = 0; i < numberOfVertices - 1; i++)
    {
        scanf("%d %d %d", &a, &b, &w); a--; b--;
        adj[a].push_back( {b, w} );
        adj[b].push_back( {a, w} );
    }
}

pair<int, int> GetFarthestVertex(int root)
{
    int dist[MaxNumberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        dist[i] = -1;
    }
    dist[root] = 0;

    int farthestVertex = root;

    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < adj[a].size(); i++)
        {
            int b = adj[a][i].first;
            int w = adj[a][i].second;

            if (dist[b] != -1)
            {
                continue;
            }

            dist[b] = dist[a] + w;
            if (dist[b] > dist[farthestVertex])
            {
                farthestVertex = b;
            }

            q.push(b);
        }
    }

    return {farthestVertex, dist[farthestVertex]};
}

int GetDiameter()
{
    return GetFarthestVertex(GetFarthestVertex(0).first).second;
}

int main()
{
    Input();
    printf("%d\n", GetDiameter());

    return 0;
}
