/*
ID: borisd22
TASK: dining
LANG: C++
*/

#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfVertices 50000
#define Infinity 2147483647

ifstream fin ("dining.in");
ofstream fout ("dining.out");

struct Edge
{
    int endVertex;
    int weight;
};

struct Vertex
{
    vector<Edge> adj;
    int haybale;
};

Vertex vertices[MaxNumberOfVertices];
int numberOfVertices;

set<int> haybaleVertices;

int distToBarn[MaxNumberOfVertices];

set<int> distsUsing[MaxNumberOfVertices];

int cowCanDine[MaxNumberOfVertices];

void Input()
{
    int numberOfEdges, numberOfHaybales;
    Read >> numberOfVertices >> numberOfEdges >> numberOfHaybales;

    int a, b, w;
    for (int i = 0; i < numberOfEdges; i++)
    {
        Read >> a >> b >> w;
        a--;
        b--;

        vertices[a].adj.push_back( {b, w} );
        vertices[b].adj.push_back( {a, w} );
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        vertices[i].haybale = -1;
    }
    int v, y;
    for (int i = 0; i < numberOfHaybales; i++)
    {
        Read >> v >> y;
        v--;

        haybaleVertices.insert(v);
        vertices[v].haybale = max(vertices[v].haybale, y);
    }
}

void Dijkstra(int root, int dist[], bool barn)
{
    bool processed[MaxNumberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        dist[i] = Infinity;
        processed[i] = false;
    }
    dist[root] = 0;

    priority_queue< pair<int, int> > q;
    q.push( {0, root} );
    while (!q.empty())
    {
        int a = q.top().second; q.pop();
        if (processed[a]) continue;
        processed[a] = true;

        for (int i = 0; i < vertices[a].adj.size(); i++)
        {
            int b = vertices[a].adj[i].endVertex, w = vertices[a].adj[i].weight;
            if (dist[a] + w < dist[b])
            {
                dist[b] = dist[a] + w;
                q.push( {-dist[b], b} );

                if (barn)
                {
                    distsUsing[a].insert(b);
                }
            }
        }
    }
}

void InitCowCanDine()
{
    for (int i = 0; i < numberOfVertices - 1; i++)
    {
        cowCanDine[i] = -1;
    }
}

void FindCowCanDine(int x)
{
    if (vertices[x].haybale != -1)
    {
        cowCanDine[x] = true;
        return;
    }
    if (cowCanDine[x] != -1)
    {
        return;
    }

    int distFromX[MaxNumberOfVertices];
    Dijkstra(x, distFromX, false);

    for (set<int>::iterator i = haybaleVertices.begin(); i != haybaleVertices.end(); i++)
    {
        int haybaleVertex = (*i);

        if (distFromX[haybaleVertex] + distToBarn[haybaleVertex] - distToBarn[x] <= vertices[haybaleVertex].haybale)
        {
            cowCanDine[x] = true;

            for (set<int>::iterator j = distsUsing[x].begin(); j != distsUsing[x].end(); j++)
            {
                cowCanDine[*j] = true;
            }
            return;
        }
    }

    cowCanDine[x] = false;
}

int main()
{
    Input();
    Dijkstra(numberOfVertices - 1, distToBarn, true);

    InitCowCanDine();
    for (int i = 0; i < numberOfVertices - 1; i++)
    {
        FindCowCanDine(i);
        if (cowCanDine[i])
        {
            Write << "1" << endl;
        }
        else
        {
            Write << "0" << endl;
        }
    }

    return 0;
}
