/*
ID: borisd22
TASK: comehome
LANG: C++
*/

#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin ("comehome.in");
ofstream fout ("comehome.out");

#define Read fin
#define Print fout
#define PB push_back
#define NumberOfVertices 52
#define Infinity 51000

struct Edge
{
    int end;
    int weight;
};

vector<Edge> adj[NumberOfVertices];

int VertexFromLetter(char l)
{
    if (l >= 'a' && l <= 'z')
    {
        return l - 'a';
    }
    else
    {
        return l - 'A' + 'z' - 'a' + 1;
    }
}

char LetterFromVertex(int v)
{
    if (v < 26)
    {
        return (char)('a' + v);
    }
    else
    {
        return (char)('A' + v - 26);
    }
}

void AddEdge(vector<Edge>& vec, Edge edge)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].end == edge.end)
        {
            vec[i].weight = min(vec[i].weight, edge.weight);
            return;
        }
    }

    vec.PB(edge);
}

void Input()
{
    int numberOfEdges;
    Read >> numberOfEdges;

    int a, b, w;
    char aLetter, bLetter;
    for (int i = 0; i < numberOfEdges; i++)
    {
        Read >> aLetter >> bLetter >> w;
        a = VertexFromLetter(aLetter);
        b = VertexFromLetter(bLetter);

        AddEdge(adj[a], {b, w});
        AddEdge(adj[b], {a, w});
    }
}

void Solve()
{
    int base = NumberOfVertices - 1;

    int dist[NumberOfVertices];
    bool processed[NumberOfVertices];
    for (int i = 0; i < NumberOfVertices; i++)
    {
        dist[i] = Infinity;
        processed[i] = false;
    }
    dist[base] = 0;

    priority_queue< pair<int, int> > q;
    q.push( {0, base} );
    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();

        if (processed[a])
        {
            continue;
        }
        processed[a] = true;

        for (int i = 0; i < adj[a].size(); i++)
        {
            int b = adj[a][i].end;
            int w = adj[a][i].weight;

            if (!processed[b])
            {
                if (dist[a] + w < dist[b])
                {
                    dist[b] = dist[a] + w;
                    q.push( {-dist[b], b});
                }
            }
        }
    }

    int bestCow = 26;
    for (int i = bestCow + 1; i < NumberOfVertices - 1; i++)
    {
        if (dist[i] < dist[bestCow])
        {
            bestCow = i;
        }
    }

    Print << LetterFromVertex(bestCow) << " " << dist[bestCow] << endl;
}

int main()
{
    Input();
    Solve();

    return 0;
}