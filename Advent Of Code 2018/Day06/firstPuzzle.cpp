//Doesn't exactly work but got me the right answer

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define Width 600
#define Height 600
#define MaxNumberOfPoints 100

struct Point
{
    int x;
    int y;
};

vector<Point> points;

int GetManhDist(Point p1, Point p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void Input()
{
    while (true)
    {
        string input;
        getline(cin, input);

        if (input == "end")
        {
            break;
        }

        int x = 0;
        int i = 0;
        while (input[i] != ',')
        {
            x *= 10;
            x += input[i++] - '0';
        }
        i += 2;
        int y = 0;
        while (i < input.length())
        {
            y *= 10;
            y += input[i++] - '0';
        }

        points.push_back({x + 50, y + 50});
    }
}

int main()
{
    Input();

    int area[MaxNumberOfPoints];
    for (int i = 0; i < points.size(); i++)
    {
        area[i] = 0;
    }

    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            vector< pair<int, int> > dists;
            for (int k = 0; k < points.size(); k++)
            {
                dists.push_back( {GetManhDist({i, j}, points[k]), k} );
            }
            sort(dists.begin(), dists.end());
            if (dists[0].first != dists[1].first)
            {
                area[dists[0].second]++;
            }
        }
    }

    for (int i = 0; i < points.size(); i++)
    {
        cout << area[i] << endl;
    }

    return 0;
}
