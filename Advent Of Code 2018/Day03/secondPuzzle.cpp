//Works

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Rectangle
{
    string ID;
    Point A;
    Point B;
};

vector<Rectangle> rects;

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

        Rectangle rect = {"", {0, 0}, {0, 0} };

        int index = 0;
        while (input[index] != ' ')
        {
            index++;
        }
        rect.ID = input.substr(1, index - 1);
        index += 3;

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

        rects.push_back(rect);
    }
}

bool Intersect(Rectangle& r1, Rectangle& r2)
{
    return r1.A.x <= r2.B.x && r1.B.x >= r2.A.x && r1.A.y <= r2.B.y && r1.B.y >= r2.A.y;
}

int main()
{
    Input();

    for (int i = 0; i < rects.size(); i++)
    {
        bool overlap = false;
        for (int j = 0; j < rects.size(); j++)
        {
            if (i == j) continue;
            if (Intersect(rects[i], rects[j]))
            {
                overlap = true;
                break;
            }
        }
        if (!overlap)
        {
            cout << rects[i].ID << endl;
            return 0;
        }
    }

    return 0;
}
