//Works

#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
#define PlaneSize 1000

int inRects[PlaneSize][PlaneSize];

struct Point
{
    int x;
    int y;
};

struct Rectangle
{
    Point A;
    Point B;
};

void Input()
{
    for (int i = 0; i < PlaneSize; i++)
    {
        for (int j = 0; j < PlaneSize; j++)
        {
            inRects[i][j] = 0;
        }
    }

    while (true)
    {
        string input;
        getline(cin, input);

        if (input == "end")
        {
            break;
        }

        Rectangle rect = { {0, 0}, {0, 0} };

        int index = 0;
        while (input[index] != '@')
        {
            index++;
        }
        index += 2;

        while (input[index] != ',')
        {
            rect.A.x *= 10;
            rect.A.x += input[index++] - '0';
        }
        index ++;
        while (input[index] != ':')
        {
            rect.A.y *= 10;
            rect.A.y += input[index++] - '0';
        }
        index += 2;
        while (input[index] != 'x')
        {
            rect.B.x *= 10;
            rect.B.x += input[index++] - '0';
        }
        index++;
        while (index < input.length())
        {
            rect.B.y *= 10;
            rect.B.y += input[index++] - '0';
        }

        rect.B.x = rect.A.x + rect.B.x - 1;
        rect.B.y = rect.A.y + rect.B.y - 1;

        for (int i = rect.A.x; i <= rect.B.x; i++)
        {
            for (int j = rect.A.y; j <= rect.B.y; j++)
            {
                inRects[i][j]++;
            }
        }
    }
}

int main()
{
    Input();

    int commonCount = 0;
    for (int i = 0; i < PlaneSize; i++)
    {
        for (int j = 0; j < PlaneSize; j++)
        {
            if (inRects[i][j] > 1)
            {
                commonCount++;
            }
        }
    }

    cout << commonCount << endl;

    return 0;
}
