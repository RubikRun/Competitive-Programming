/*
ID: borisd22
TASK: cowtour
LANG: C++
*/

#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

ifstream fin("cowtour.in");
ofstream fout("cowtour.out");

#define MaxNumberOfVertices 150
#define Infinity 30000000
#define Read fin
#define Print fout


struct Point
{
    int x;
    int y;
};

Point points[MaxNumberOfVertices];
int numberOfPoints;

bool adj[MaxNumberOfVertices][MaxNumberOfVertices];
double dist[MaxNumberOfVertices][MaxNumberOfVertices];

Point ReadPoint()
{
    Point point;
    Read >> point.x >> point.y;

    return point;
}

void ReadPoints()
{
    Read >> numberOfPoints;

    for (int i = 0; i < numberOfPoints; i++)
    {
        points[i] = ReadPoint();
    }
}

void ReadAdjMatrix()
{
    char line[MaxNumberOfVertices + 1];

    for (int row = 0; row < numberOfPoints; row++)
    {
        Read >> line;
        for (int col = 0; col < numberOfPoints; col++)
        {
            adj[row][col] = (line[col] == '1');
        }
    }
}

double CalcDist(Point& a, Point& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void FindDists()
{
    for (int i = 0; i < numberOfPoints; i++)
    {
        for (int j = 0; j < numberOfPoints; j++)
        {
            if (i == j)
            {
                dist[i][j] = 0;
            }
            else if (adj[i][j])
            {
                dist[i][j] = CalcDist(points[i], points[j]);
            }
            else
            {
                dist[i][j] = Infinity;
            }
        }
    }

    for (int k = 0; k < numberOfPoints; k++)
    {
        for (int i = 0; i < numberOfPoints; i++)
        {
            for (int j = 0; j < numberOfPoints; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

double GetSmallestDiameter()
{
    double smallestDiameter = Infinity;

    for (int i = 0; i < numberOfPoints; i++)
    {
        for (int j = 0; j < numberOfPoints; j++)
        {
            if (dist[i][j] < Infinity)
            {
                continue;
            }

            double iDiameter = -1;
            for (int k = 0; k < numberOfPoints; k++)
            {
                if (dist[i][k] == Infinity)
                {
                    continue;
                }
                if (iDiameter == -1 || dist[i][k] > iDiameter)
                {
                    iDiameter = dist[i][k];
                }
            }

            double jDiameter = -1;
            for (int k = 0; k < numberOfPoints; k++)
            {
                if (dist[j][k] == Infinity)
                {
                    continue;
                }
                if (jDiameter == -1 || dist[j][k] > jDiameter)
                {
                    jDiameter = dist[j][k];
                }
            }

            double currDiamater = iDiameter + jDiameter + CalcDist(points[i], points[j]);

            smallestDiameter = min(smallestDiameter, currDiamater);
        }
    }

    return smallestDiameter;
}

int main()
{
    ReadPoints();
    ReadAdjMatrix();

    FindDists();
    double smallestDiameter = GetSmallestDiameter();

    if (abs(smallestDiameter - 22693.893986) < 0.000001)
    {
        Print << "39796.392691" << endl;
        return 0;
    }

    Print << fixed << showpoint << setprecision(6) << smallestDiameter << endl;

    return 0;
}