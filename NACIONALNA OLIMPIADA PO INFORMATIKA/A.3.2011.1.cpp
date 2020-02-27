//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MaxNumberOfSegments 100

struct Point
{
    int coord[2];
};

struct Segment
{
    Point endpoints[2];
};

Segment segments[MaxNumberOfSegments];
int numberOfSegments;

void Input()
{
    scanf("%d", &numberOfSegments);

    for (int i = 0; i < numberOfSegments; i++)
    {
        scanf("%d %d %d %d", &segments[i].endpoints[0].coord[0], &segments[i].endpoints[0].coord[1], &segments[i].endpoints[1].coord[0], &segments[i].endpoints[1].coord[1]);
    }
}

bool Intersects(Point& a, Point& b, int x)
{
    if (a.coord[0] == b.coord[0])
    {
        return ((segments[x].endpoints[0].coord[0] - a.coord[0]) * (segments[x].endpoints[1].coord[0] - a.coord[0]) <= 0);
    }

    double slope = (double)(b.coord[1] - a.coord[1]) / (b.coord[0] - a.coord[0]);
    double height = a.coord[1] - slope * a.coord[0];

    return ((slope * segments[x].endpoints[0].coord[0] + height - segments[x].endpoints[0].coord[1]) *
    (slope * segments[x].endpoints[1].coord[0] + height - segments[x].endpoints[1].coord[1]) <= 0);
}

int GetMaxNumberOfIntersectedSegments()
{
    int result = 1;

    for (int i = 0; i < numberOfSegments - 1; i++)
    {
        for (int j = i + 1; j < numberOfSegments; j++)
        {
            for (int p = 0; p < 2; p++)
            {
                for (int q = 0; q < 2; q++)
                {
                    int segmentsCount = 2;
                    for (int k = 0; k < numberOfSegments; k++)
                    {
                        if (k == i || k == j)
                        {
                            continue;
                        }
                        if (Intersects(segments[i].endpoints[p], segments[j].endpoints[q], k))
                        {
                            segmentsCount++;
                        }
                    }
                    result = max(result, segmentsCount);
                }
            }
        }
    }

    return result;
}

int main()
{
    Input();

    printf("%d\n", GetMaxNumberOfIntersectedSegments());

    return 0;
}
