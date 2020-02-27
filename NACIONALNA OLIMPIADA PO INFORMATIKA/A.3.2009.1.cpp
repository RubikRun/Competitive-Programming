//checked - 100%

#include <cstdio>
#include <set>
#include <vector>
#include <cmath>

using namespace std;
#define PI 3.14159265359

struct Point
{
    int x;
    int y;

    bool operator<(const Point &p) const
    {
        if (x == p.x)
        {
            return y < p.y;
        }
        return x < p.x;
    }
};

set<Point> points;

int mineRadius;

void Input()
{
    int numberOfInputPoints;
    scanf("%d %d", &numberOfInputPoints, &mineRadius);

    Point point;
    for (int i = 0; i < numberOfInputPoints; i++)
    {
        scanf("%d %d", &point.x, &point.y);
        points.insert(point);
    }
}

bool Clockwise(Point a, Point b, Point c)
{
    return (a.x - b.x) * (c.y - b.y) < (a.y - b.y) * (c.x - b.x);
}

vector<Point> GetConvexHull()
{
    vector<Point> convexHull;

    set<Point>::iterator it = points.begin();
    convexHull.push_back(*it);

    do
    {
        Point nextPoint = {-1, -1};
        for (it = points.begin(); it != points.end(); it++)
        {
            if ((*it).x == convexHull.back().x && (*it).y == convexHull.back().y)
            {
                continue;
            }
            if ((*it).x == convexHull[convexHull.size() - 2].x && (*it).y == convexHull[convexHull.size() - 2].y)
            {
                continue;
            }
            if (nextPoint.x == -1)
            {
                nextPoint = *it;
                continue;
            }
            if (!Clockwise(convexHull.back(), nextPoint, *it))
            {
                nextPoint = *it;
            }
        }

        convexHull.push_back(nextPoint);
    } while (convexHull[0].x != convexHull.back().x || convexHull[0].y != convexHull.back().y);

    return convexHull;
}

double GetDist(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
    Input();

    if (points.size() == 1)
    {
        printf("%.3lf\n", 2 * PI * mineRadius);
        return 0;
    }
    if (points.size() == 2)
    {
        set<Point>::iterator a = points.begin();
        set<Point>::iterator b = points.begin();
        b++;
        printf("%.3lf\n", 2 * PI * mineRadius + 2 * GetDist(*a, *b));
        return 0;
    }
    vector<Point> convexHull = GetConvexHull();

    double length = 2 * PI * mineRadius;
    for (int i = 0; i < convexHull.size() - 1; i++)
    {
        length += GetDist(convexHull[i], convexHull[i + 1]);
    }

    printf("%.3lf\n", length);

    return 0;
}
