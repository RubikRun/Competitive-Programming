//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxNumberOfPoints 9

struct Point
{
    int x;
    int y;
};

struct Graph
{
    int numberOfVertices, numberOfEdges;
    int weight[MaxNumberOfPoints][MaxNumberOfPoints];
};

Point ReadPoint()
{
    Point point;
    scanf("%d%d", &point.x, &point.y);

    return point;
}

int Distance(Point point1, Point point2)
{
    return abs(point1.x - point2.x) + abs(point1.y - point2.y);
}

Graph ConstructGraph(Point points[], int numberOfPoints)
{
    Graph graph;

    graph.numberOfVertices = numberOfPoints;
    graph.numberOfEdges = graph.numberOfVertices * (graph.numberOfVertices - 1) / 2;

    for (int firstVertex = 0; firstVertex < graph.numberOfVertices; firstVertex++)
    {
        for (int secondVertex = firstVertex + 1; secondVertex < graph.numberOfVertices; secondVertex++)
        {
            graph.weight[firstVertex][secondVertex] = Distance(points[firstVertex], points[secondVertex]);
            graph.weight[secondVertex][firstVertex] = graph.weight[firstVertex][secondVertex];
        }
    }

    return graph;
}

int GetPathLen(int path[], Graph graph)
{
    int pathLen = 0;

    for (int i = 0; i < graph.numberOfVertices - 1; i++)
    {
        pathLen += graph.weight[path[i]][path[i+1]];
    }

    return pathLen;
}

int MinFullPathLen(Graph graph)
{
    int path[MaxNumberOfPoints];
    for (int vertex = 0; vertex < graph.numberOfVertices; vertex++)
    {
        path[vertex] = vertex;
    }
    int minFullPathLen = GetPathLen(path, graph);

    int currentPathLen;
    while (next_permutation(path, path + graph.numberOfVertices))
    {
        currentPathLen = GetPathLen(path, graph);
        if (currentPathLen < minFullPathLen)
        {
            minFullPathLen = currentPathLen;
        }
    }

    return minFullPathLen;
}

int main()
{
    int numberOfPoints;
    scanf("%d", &numberOfPoints);

    Point points[MaxNumberOfPoints];
    for (int pointIndex = 0; pointIndex < numberOfPoints; pointIndex++)
    {
        points[pointIndex] = ReadPoint();
    }

    Graph graph = ConstructGraph(points, numberOfPoints);
    int minFullPathLen = MinFullPathLen(graph);

    printf("%d\n", minFullPathLen);

    return 0;
}
