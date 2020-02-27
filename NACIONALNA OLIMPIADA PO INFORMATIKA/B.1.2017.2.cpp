//checked - 100%

#include <cstdio>
using namespace std;

struct Point
{
    int dimension[2];
};

Point ReadPoint()
{
    Point point;

    scanf("%d", &point.dimension[0]);
    scanf("%d", &point.dimension[1]);

    return point;
}

void SwapPoints(Point& A, Point& B)
{
    Point holder = A;
    A = B;
    B = holder;
}

void SortPoints(Point& A, Point& B)
{
    if (A.dimension[0] > B.dimension[0] || A.dimension[1] > B.dimension[1])
    {
        SwapPoints(A, B);
    }
}

struct Segment
{
    Point A;
    Point B;
};

Segment ReadSegment()
{
    Segment segment;

    segment.A = ReadPoint();
    segment.B = ReadPoint();

    SortPoints(segment.A, segment.B);

    return segment;
}

int GetSingleDimensionDistance(Segment segment1, Segment segment2, int dimension)
{
    if (segment2.A.dimension[dimension] - segment1.B.dimension[dimension] >= 0)
    {
        return segment2.A.dimension[dimension] - segment1.B.dimension[dimension];
    }
    if (segment1.A.dimension[dimension] - segment2.B.dimension[dimension] >= 0)
    {
        return segment1.A.dimension[dimension] - segment2.B.dimension[dimension];
    }

    return 0;
}

int GetDistance(Segment segment1, Segment segment2)
{
    return GetSingleDimensionDistance(segment1, segment2, 0) + GetSingleDimensionDistance(segment1, segment2, 1);
}

int main()
{
    Segment segment1 = ReadSegment();
    Segment segment2 = ReadSegment();

    int distance = GetDistance(segment1, segment2);

    printf("%d\n", distance);

    return 0;
}