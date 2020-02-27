//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxNumberOfEndPoints 1998

struct EndPoint
{
    int coordinate;
    bool opening;
};

bool EndPointsComparator(EndPoint endPoint1, EndPoint endPoint2)
{
    return endPoint1.coordinate < endPoint2.coordinate;
}

int main()
{
    int numberOfSegments;
    scanf("%d", &numberOfSegments);

    int numberOfEndpoints = numberOfSegments * 2;

    EndPoint endPoints[MaxNumberOfEndPoints];
    for (int i = 0; i < numberOfEndpoints; i++)
    {
        scanf("%d", &endPoints[i].coordinate);
        endPoints[i].opening = (i % 2 == 0);
    }

    sort(endPoints, endPoints + numberOfEndpoints, EndPointsComparator);

    int numberOfAreas = 0, maxAreaLen = 0, depth = 0, currentAreaBegin, currentAreaLen, lastAreaEnd;
    for (int endPointIndex = 0; endPointIndex < numberOfEndpoints; endPointIndex++)
    {
        if (endPoints[endPointIndex].opening)
        {
            if (depth == 0 && endPoints[endPointIndex].coordinate != lastAreaEnd)
            {
                currentAreaBegin = endPoints[endPointIndex].coordinate;
                numberOfAreas++;
            }
            depth++;
        }
        else
        {
            depth--;
            if (depth == 0)
            {
                lastAreaEnd = endPoints[endPointIndex].coordinate;
                currentAreaLen = lastAreaEnd - currentAreaBegin;

                if (currentAreaLen > maxAreaLen)
                {
                    maxAreaLen = currentAreaLen;
                }
            }
        }
    }

    printf("%d %d\n", numberOfAreas, maxAreaLen);

    return 0;
}