//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxNumberOfSegments 10000

struct EndPoint
{
    int x;
    int type;
};

bool EndPointComparator(EndPoint& endPoint1, EndPoint& endPoint2)
{
    return endPoint1.x < endPoint2.x;
}

struct MultiPoint
{
    int x;
    int openSum;
    int closeSum;
};

struct Interval
{
    int first, last;
    int color;
};

void EndPointsToMultiPoints(EndPoint endPoints[], int numberOfEndPoints, MultiPoint multiPoints[], int& numberOfMultiPoints)
{
    numberOfMultiPoints = 0;
    multiPoints[0].x = endPoints[0].x;
    multiPoints[0].openSum = multiPoints[0].closeSum = 0;

    for (int i = 0; i < numberOfEndPoints; i++)
    {
        if (i > 0 && endPoints[i].x != endPoints[i - 1].x)
        {
            numberOfMultiPoints++;
            multiPoints[numberOfMultiPoints].x = endPoints[i].x;
            multiPoints[numberOfMultiPoints].openSum = multiPoints[numberOfMultiPoints].closeSum = 0;
        }

        multiPoints[numberOfMultiPoints].openSum += (endPoints[i].type == 1);
        multiPoints[numberOfMultiPoints].closeSum -= (endPoints[i].type == -1);
    }
    numberOfMultiPoints++;
}

void MultiPointsToIntervals(MultiPoint multiPoints[], int numberOfMultiPoints, Interval intervals[], int& numberOfIntervals)
{
    numberOfIntervals = 0;

    int typeSum = 0;
    for (int i = 0; i < numberOfMultiPoints - 1; i++)
    {
        typeSum += multiPoints[i].openSum;

        intervals[numberOfIntervals].first = intervals[numberOfIntervals].last = multiPoints[i].x;
        intervals[numberOfIntervals++].color = typeSum % 2;

        typeSum += multiPoints[i].closeSum;

        if (multiPoints[i].x + 1 == multiPoints[i + 1].x)
        {
            continue;
        }

        intervals[numberOfIntervals].first = multiPoints[i].x + 1;
        intervals[numberOfIntervals].last = multiPoints[i + 1].x - 1;
        if (i == numberOfMultiPoints - 2)
        {
            intervals[numberOfIntervals].last++;
        }
        intervals[numberOfIntervals++].color = typeSum % 2;
    }
}

int GetLongestConsecutiveBlack(Interval intervals[], int numberOfIntervals)
{
    int black = 0, maxBlack = 0;
    for (int i = 0; i < numberOfIntervals; i++)
    {
        if (intervals[i].color)
        {
            black += intervals[i].last - intervals[i].first + 1;
        }
        else
        {
            maxBlack = max(black, maxBlack);
            black = 0;
        }
    }
    maxBlack = max(black, maxBlack);

    return maxBlack;
}

int main()
{
    int numberOfSegments;
    scanf("%d", &numberOfSegments);

    int numberOfEndPoints = numberOfSegments * 2;

    EndPoint endPoints[MaxNumberOfSegments * 2];
    for (int i = 0; i < numberOfEndPoints; i++)
    {
        scanf("%d", &endPoints[i].x);
        endPoints[i].type = (i % 2 == 0) ? 1 : -1;
    }

    sort(endPoints, endPoints + numberOfEndPoints, EndPointComparator);

    MultiPoint multiPoints[MaxNumberOfSegments * 2];
    int numberOfMultiPoints;
    EndPointsToMultiPoints(endPoints, numberOfEndPoints, multiPoints, numberOfMultiPoints);

    Interval intervals[MaxNumberOfSegments * 4];
    int numberOfIntervals;
    MultiPointsToIntervals(multiPoints, numberOfMultiPoints, intervals, numberOfIntervals);

    int longestConsecutiveBlack = GetLongestConsecutiveBlack(intervals, numberOfIntervals);

    printf("%d\n", longestConsecutiveBlack);

    return 0;
}