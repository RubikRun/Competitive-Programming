//checked - 100%

#include <cstdio>

using namespace std;

#define MaxNumberOfLines 100

struct Point
{
    int x, y;
};

struct Line
{
    Point A, B;
};

void ReadPoint(Point& point)
{
    scanf("%d %d", &point.x, &point.y);
}

void ReadLine(Line& line)
{
    ReadPoint(line.A);
    ReadPoint(line.B);
}

bool SameSlope(Line& line1, Line& line2)
{
    return (line1.A.x - line1.B.x) * (line2.A.y - line2.B.y) == (line1.A.y - line1.B.y) * (line2.A.x - line2.B.x);
}

int main()
{
    Line slopes[MaxNumberOfLines];
    int numberOfSlopes = 0;

    int numberOfLines;
    scanf("%d", &numberOfLines);

    Line currentLine;
    for (int i = 0; i < numberOfLines; i++)
    {
        ReadLine(currentLine);

        bool unique = true;
        for (int j = 0; j < numberOfSlopes; j++)
        {
            if (SameSlope(currentLine, slopes[j]))
            {
                unique = false;
                break;
            }
        }

        if (unique)
        {
            slopes[numberOfSlopes++] = currentLine;
        }
    }

    printf("%d\n", numberOfSlopes);

    return 0;
}