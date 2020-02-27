//checked - 100%

#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x, y;
};

int GetTraignelArea(Point& A, Point& B, Point& C) //Gets area doubled
{
    return abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}

int main()
{
    vector<Point> points;
    for (int i = 0; i < 4; i++)
    {
        points.push_back({});
        cin >> points.back().x >> points.back().y;

        for (int j = 0; j < points.size() - 1; j++)
        {
            if (points.back().x == points[j].x && points.back().y == points[j].y)
            {
                points.erase(points.end() - 1);
            }
        }
    }

    #define GiveAnswer(n) cout << n << endl; return 0;

    if (points.size() < 3)
    {
        GiveAnswer(0)
    }

    if (points.size() == 3)
    {
        if (GetTraignelArea(points[0], points[1], points[2]) == 0)
        {
            GiveAnswer(0)
        }
        else
        {
            GiveAnswer(1)
        }
    }

    int area1 = GetTraignelArea(points[0], points[1], points[2]);
    int area2 = GetTraignelArea(points[0], points[1], points[3]);
    int area3 = GetTraignelArea(points[0], points[2], points[3]);
    int area4 = GetTraignelArea(points[1], points[2], points[3]);

    if (area1 == 0 && area2 == 0 && area3 == 0 && area4 == 0)
    {
        GiveAnswer(0)
    }

    if (area1 == 0 || area2 == 0 || area3 == 0 || area4 == 0)
    {
        GiveAnswer(2)
    }

    if (area1 + area2 + area3 == area4 || area1 + area2 + area4 == area3 || area1 + area3 + area4 == area2 || area2 + area3 + area4 == area1)
    {
        GiveAnswer(3)
    }

    GiveAnswer(4)
}