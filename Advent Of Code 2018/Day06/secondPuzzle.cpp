//Works

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define SumDistLimit 10000

struct Point
{
    int x;
    int y;
};

vector<Point> points;

int leftCorner, rightCorner;
int upCorner, downCorner;

void Input()
{
    leftCorner = 1 << 30;
    rightCorner = -1 << 30;
    upCorner = 1 << 30;
    downCorner = -1 << 30;

    while (true)
    {
        string input;
        getline(cin, input);

        if (input == "end")
        {
            break;
        }

        int x = 0, y = 0;
        int i = 0;

        while (input[i] != ',')
        {
            x *= 10;
            x += input[i++] - '0';
        }
        i += 2;
        while (i < input.length())
        {
            y *= 10;
            y += input[i++] - '0';
        }

        leftCorner = min(leftCorner, x);
        rightCorner = max(rightCorner, x);
        upCorner = min(upCorner, y);
        downCorner = max(downCorner, y);

        points.push_back( {x, y} );
    }
}

int GetManhDist(Point p1, Point p2) { return abs(p1.x - p2.x) + abs(p1.y - p2.y); }

int GetSumDist(int x, int y)
{
    int sumDist = 0;
    for (int i = 0; i < points.size(); i++)
    {
        sumDist += GetManhDist({x, y}, points[i]);
    }
    return sumDist;
}

int GetCloseArea()
{
    int closeArea = 0;

    for (int i = leftCorner; i <= rightCorner; i++)
    {
        for (int j = upCorner; j <= downCorner; j++)
        {
            if (GetSumDist(i, j) < SumDistLimit)
            {
                closeArea++;
            }
        }
    }

    return closeArea;
}

bool Expand(int& closeArea)
{
    int newArea = 0;

    leftCorner--;
    rightCorner++;
    upCorner--;
    downCorner++;

    for (int i = leftCorner; i <= rightCorner; i++)
    {
        if (GetSumDist(i, upCorner) < SumDistLimit) newArea++;
        if (GetSumDist(i, downCorner) < SumDistLimit) newArea++;
    }
    for (int j = upCorner + 1; j <= downCorner - 1; j++)
    {
        if (GetSumDist(leftCorner, j) < SumDistLimit) newArea++;
        if (GetSumDist(rightCorner, j) < SumDistLimit) newArea++;
    }

    closeArea += newArea;
    return (newArea > 0);
}

int main()
{
    Input();

    int closeArea = GetCloseArea();
    while (Expand(closeArea));

    cout << closeArea << endl;

    return 0;
}
