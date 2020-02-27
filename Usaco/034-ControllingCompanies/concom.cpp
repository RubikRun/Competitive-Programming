/*
ID: borisd22
TASK: concom
LANG: C++
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin ("concom.in");
ofstream fout ("concom.out");

#define MaxNumberOfVertices 100

struct Edge
{
    int end;
    int weight;
};

struct Graph
{
    int numberOfVertices;
    vector<Edge> outEdges[MaxNumberOfVertices];
    vector<int> controlled[MaxNumberOfVertices];
};

Graph ReadGraph()
{
    Graph graph;
    graph.numberOfVertices = 0;

    int numberOfEdges;
    fin >> numberOfEdges;

    int a, b, w;
    for (int i = 0; i < numberOfEdges; i++)
    {
        fin >> a >> b >> w;
        graph.numberOfVertices = max(graph.numberOfVertices, max(a, b));
        a--;
        b--;

        graph.outEdges[a].push_back( {b, w} );
    }

    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        graph.controlled[i] = {i};
    }

    return graph;
}

void VertexControl(int root, Graph& graph)
{
    bool foundNew = true;

    while (foundNew)
    {
        foundNew = false;

        int ownSum[MaxNumberOfVertices];
        for (int i = 0; i < graph.numberOfVertices; i++)
        {
            ownSum[i] = 0;
        }
        for (int i = 0; i < graph.controlled[root].size(); i++)
        {
            int currentControlled = graph.controlled[root][i];

            for (int j = 0; j < graph.outEdges[currentControlled].size(); j++)
            {
                ownSum[graph.outEdges[currentControlled][j].end] += graph.outEdges[currentControlled][j].weight;
            }
        }
        for (int i = 0; i < graph.numberOfVertices; i++)
        {
            if (ownSum[i] > 50)
            {
                bool found = false;
                for (int j = 0; j < graph.controlled[root].size(); j++)
                {
                    if (graph.controlled[root][j] == i)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    graph.controlled[root].push_back(i);
                    foundNew = true;
                }
            }
        }
    }
}

void AllVerticesControl(Graph& graph)
{
    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        VertexControl(i, graph);
    }
}

int main()
{
    Graph graph = ReadGraph();

    AllVerticesControl(graph);

    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        sort(graph.controlled[i].begin(), graph.controlled[i].end());

        for (int j = 0; j < graph.controlled[i].size(); j++)
        {
            if (i != graph.controlled[i][j])
            {
                fout << i + 1 << " " << graph.controlled[i][j] + 1 << endl;
            }
        }
    }

    return 0;
}

