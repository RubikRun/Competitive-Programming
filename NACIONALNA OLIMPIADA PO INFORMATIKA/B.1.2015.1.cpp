//checked - 100%

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

void SwapEm(long long& x, long long& y)
{
    long long holder = x;
    x = y;
    y = holder;
}

long long GetDistance(long long x1, long long y1, long long x2, long long y2)
{
    double realDistance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    long long distanceNeeded = (long long)ceil(realDistance);

    return distanceNeeded;
}

int main()
{
    long long x, y;
    long long left, right, down, up;
    cin >> x >> y;
    cin >> left >> down;
    cin >> right >> up;

    if (left > right)
    {
        SwapEm(left, right);
    }
    if (down > up)
    {
        SwapEm(down, up);
    }

    if (x >= left && x <= right && y >= down && y <= up)
    {
        cout << 0 << endl;
        return 0;
    }

    long long answer;
    if (y >= down && y <= up)
    {
        if (x > right)
        {
            answer = x - right;
        }
        else
        {
            answer = left - x;
        }
    }
    else if (x >= left && x <= right)
    {
        if (y > up)
        {
            answer = y - up;
        }
        else
        {
            answer = down - y;
        }
    }
    else
    {
        long long closestX = left, closestY = down;
        if (abs(right - x) < abs(left - x))
        {
            closestX = right;
        }
        if (abs(up - y) < abs(down - y))
        {
            closestY = up;
        }

        answer = GetDistance(x, y, closestX, closestY);
    }

    cout << answer << endl;

    return 0;
}