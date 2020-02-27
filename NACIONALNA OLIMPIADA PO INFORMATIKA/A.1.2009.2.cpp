//checked - 100%

#include <cstdio>
#include <queue>
using namespace std;

#define MaxNumberOfVertices 1000

struct Graph
{
    int numberOfVertices;
    int numberOfEdges;

    bool areConnected[MaxNumberOfVertices][MaxNumberOfVertices];
};

Graph ReadGraph()
{
    Graph graph;

    scanf("%d", &graph.numberOfVertices);
    scanf("%d", &graph.numberOfEdges);

    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        for (int j = 0; j < graph.numberOfVertices; j++)
        {
            graph.areConnected[i][j] = true;
        }
    }
    int a, b;
    for (int i = 0; i < graph.numberOfEdges; i++)
    {
        scanf("%d %d", &a, &b);
        a--;
        b--;
        graph.areConnected[a][b] = false;
        graph.areConnected[b][a] = false;
    }

    return graph;
}

void CheckComponent(Graph& graph, int node, bool checked[])
{
    queue<int> waitingVertices;

    waitingVertices.push(node);
    int currentVertex;
    while (!waitingVertices.empty())
    {
        currentVertex = waitingVertices.front();
        waitingVertices.pop();
        checked[currentVertex] = true;

        for (int potentialChild = 0; potentialChild < graph.numberOfVertices; potentialChild++)
        {
            if (graph.areConnected[currentVertex][potentialChild] && !checked[potentialChild])
            {
                waitingVertices.push(potentialChild);
            }
        }
    }
}

void FillArrayWithFalse(bool arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = false;
    }
}

int CountComponents(Graph& graph)
{
    bool checked[MaxNumberOfVertices];
    FillArrayWithFalse(checked, graph.numberOfVertices);

    int numberOfComponents = 0;

    for (int vertex = 0; vertex < graph.numberOfVertices; vertex++)
    {
        if (!checked[vertex])
        {
            numberOfComponents++;
            CheckComponent(graph, vertex, checked);
        }
    }

    return numberOfComponents;
}

int main()
{
    Graph graph = ReadGraph();

    int numberOfComponents = CountComponents(graph);

    printf("%d\n", numberOfComponents - 1);

    return 0;
}