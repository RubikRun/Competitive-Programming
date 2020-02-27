//checked - 100%

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define MaxNumberOfPoints 300000

void SwapEm(int& a, int& b)
{
    int holder = a;
    a = b;
    b = holder;
}

struct Point
{
    int coordinate;
    int type;
    int index;
    int depth;
};

bool PointComparatorForDepth(Point point1, Point point2)
{
    if (point1.coordinate == point2.coordinate)
    {
        return point1.type > point2.type;
    }

    return point1.coordinate < point2.coordinate;
}

bool PointComparatorForPrinting(Point point1, Point point2)
{
    if (point1.type == point2.type)
    {
        return point1.index < point2.index;
    }

    return abs(point1.type) < abs(point2.type);
}

void CalcAskingPointsDepths(Point points[], int numberOfPoints)
{
    sort(points, points + numberOfPoints, PointComparatorForDepth);

    int currentDepth = 0;
    for (int pointIndex = 0; pointIndex < numberOfPoints; pointIndex++)
    {
        if (points[pointIndex].type == 0)
        {
            points[pointIndex].depth = currentDepth;
        }
        else
        {
            currentDepth += points[pointIndex].type;
        }
    }
}

void PrintAskingPointsDepths(Point points[], int numberOfPoints)
{
    sort(points, points + numberOfPoints, PointComparatorForPrinting);

    int pointIndex = 0;
    while (points[pointIndex + 1].type == 0)
    {
        printf("%d ", points[pointIndex].depth);

        pointIndex++;
    }
    printf("%d\n", points[pointIndex].depth);
}

int main()
{
    int numberOfSegments, numberOfAskingPoints;
    scanf("%d%d", &numberOfSegments, &numberOfAskingPoints);

    Point points[MaxNumberOfPoints];
    int numberOfPoints = 0;

    for (int i = 0; i < numberOfSegments; i++)
    {
        scanf("%d", &points[numberOfPoints].coordinate);
        points[numberOfPoints++].type = 1;
        scanf("%d", &points[numberOfPoints].coordinate);
        points[numberOfPoints++].type = -1;

        if (points[numberOfPoints - 1].coordinate < points[numberOfPoints - 2].coordinate)
        {
            SwapEm(points[numberOfPoints - 1].coordinate, points[numberOfPoints - 2].coordinate);
        }
    }
    for (int i = 0; i < numberOfAskingPoints; i++)
    {
        scanf("%d", &points[numberOfPoints].coordinate);
        points[numberOfPoints].type = 0;
        points[numberOfPoints++].index = i;
    }

    CalcAskingPointsDepths(points, numberOfPoints);
    PrintAskingPointsDepths(points, numberOfPoints);

    return 0;
}
