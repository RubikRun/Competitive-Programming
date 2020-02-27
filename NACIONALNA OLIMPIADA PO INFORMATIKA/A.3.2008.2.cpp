//checked - 40%

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define MaxNumberOfPoints 49
#define Infinity 1000000000

struct Point { int x, y; };

int numberOfPoints, numberOfVertices;

Point points[MaxNumberOfPoints];
vector<Point> chosenVertices;

bool isChosen[MaxNumberOfPoints];
int minArea;

int GetTriangleArea(Point a, Point b, Point c) { return abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)); }

bool CurveIsConstant(Point a, Point b, Point c, Point d) { return (((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) * ((c.x - b.x) * (d.y - b.y) - (c.y - b.y) * (d.x - b.x)) > 0); }

bool SegmentsIntersect(Point a, Point b, Point c, Point d)
{
    return (((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) * ((b.x - a.x) * (d.y - a.y) - (b.y - a.y) * (d.x - a.x)) < 0
    && ((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x)) * ((d.x - c.x) * (b.y - c.y) - (d.y - c.y) * (b.x - c.x)) < 0);
}

int GetConvexPolygonArea(vector<Point> vertices)
{
    if (vertices.size() < 3)
    {
        return 0;
    }
    if (vertices.size() == 3)
    {
        return GetTriangleArea(vertices[0], vertices[1], vertices[2]);
    }

    int area = 0;

    vector<Point> halfVertices;
    for (int i = 0; i <= vertices.size() / 2; i++)
    {
        halfVertices.push_back(vertices[i]);
    }
    area += GetConvexPolygonArea(halfVertices);

    halfVertices.clear();
    halfVertices.push_back(vertices[0]);
    for (int i = vertices.size() - 1; i >= vertices.size() / 2; i--)
    {
        halfVertices.push_back(vertices[i]);
    }
    area += GetConvexPolygonArea(halfVertices);

    return area;
}

void Input()
{
    cin >> numberOfPoints >> numberOfVertices;

    for (int i = 0; i < numberOfPoints; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
}

void FindMinArea()
{
    if (chosenVertices.size() == numberOfVertices)
    {
        for (int i = 0; i < chosenVertices.size(); i++)
        {
            if (!CurveIsConstant(chosenVertices[i], chosenVertices[(i + 1) % chosenVertices.size()],
             chosenVertices[(i + 2) % chosenVertices.size()], chosenVertices[(i + 3) % chosenVertices.size()]))
            {
                return;
            }
        }
        minArea = min(minArea, GetConvexPolygonArea(chosenVertices));
        return;
    }

    for (int i = 0; i < numberOfPoints; i++)
    {
        if (isChosen[i])
        {
            continue;
        }
        bool intersection = false;
        for (int j = 0; j + 2 < chosenVertices.size(); j++)
        {
            if (SegmentsIntersect(chosenVertices[j], chosenVertices[j + 1], chosenVertices.back(), points[i]))
            {
                intersection = true;
                break;
            }
        }
        if (intersection)
        {
            continue;
        }

        chosenVertices.push_back(points[i]);
        isChosen[i] = true;

        FindMinArea();

        chosenVertices.pop_back();
        isChosen[i] = false;
    }
}

int main()
{
    Input();
    for (int i = 0; i < numberOfPoints; i++) isChosen[i] = false;
    minArea = Infinity;

    FindMinArea();

    if (minArea == Infinity)
    {
        cout << 0 << endl;
        return 0;
    }

    cout << minArea / 2 << endl;

    return 0;
}
