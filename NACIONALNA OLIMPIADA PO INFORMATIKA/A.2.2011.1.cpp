//checked - 100%

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define MaxNumberOfPoints 12
#define MaxNumberOfStops 6
#define MaxPathLength 24000

struct Point
{
    int x;
    int y;
};

Point points[MaxNumberOfPoints];
int numberOfPoints;

int stops[MaxNumberOfStops];
int numberOfStops;

int dist[MaxNumberOfPoints][MaxNumberOfPoints];

int bestPathLength;

int GetDist(Point& a, Point& b)
{
    return max(abs(a.x - b.x), abs(a.y - b.y));
}

void FindAllDist()
{
    for (int i = 0; i < numberOfPoints; i++)
    {
        for (int j = i; j < numberOfPoints; j++)
        {
            dist[i][j] = dist[j][i] = GetDist(points[i], points[j]);
        }
    }
}

void ReadPoints()
{
    scanf("%d", &numberOfStops);
    numberOfPoints = numberOfStops * 2;

    for (int i = 0; i < numberOfPoints; i++)
    {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
}

int GetPathLength()
{
    Point origin = {0, 0};

    int length = GetDist(origin, points[stops[0]]);

    for (int i = 0; i < numberOfStops - 1; i++)
    {
        length += dist[stops[i]][stops[i + 1]];
    }

    return length;
}

void FindBestPathLength(int currStop)
{
    if (currStop == numberOfStops)
    {
        bestPathLength = min(bestPathLength, GetPathLength());
        return;
    }

    for (int i = 0; i < numberOfPoints; i++)
    {
        bool used = false;
        for (int j = 0; j < currStop; j++)
        {
            if (stops[j] == i)
            {
                used = true;
            }
        }
        if (used)
        {
            continue;
        }

        stops[currStop] = i;
        FindBestPathLength(currStop + 1);
    }
}

int main()
{
    ReadPoints();
    FindAllDist();

    bestPathLength = MaxPathLength;
    FindBestPathLength(0);
    printf("%d\n", bestPathLength);

    return 0;
}
