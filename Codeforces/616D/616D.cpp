#include <cstdio>
#include <algorithm>

using namespace std;
#define MaxNumberOfElements 500000
#define MaxElementValue 1000000

int elements[MaxNumberOfElements];
int numberOfElements;
int largestElementValue;

int diffValueLimit;

int currSegmentBegin;
int numberOfDiffValues;

int lastIndex[MaxElementValue + 1];

void Input()
{
    scanf("%d %d", &numberOfElements, &diffValueLimit);

    largestElementValue = 0;
    for (int i = 0; i < numberOfElements; i++)
    {
        scanf("%d", &elements[i]);
        largestElementValue = max(largestElementValue, elements[i]);
    }
}

pair<int, int> GetLongestSegment()
{
    #define UpdateLongestSegment if (longestSegment.second - longestSegment.first + 1 < currSegmentEnd - currSegmentBegin + 1) longestSegment = {currSegmentBegin, currSegmentEnd};
    pair<int, int> longestSegment = {0, 0};

    currSegmentBegin = 0;
    numberOfDiffValues = 1;

    for (int i = 0; i <= largestElementValue; i++)
    {
        lastIndex[i] = -1;
    }
    lastIndex[elements[0]] = 0;

    for (int currSegmentEnd = 1; currSegmentEnd < numberOfElements; currSegmentEnd++)
    {
        if (lastIndex[elements[currSegmentEnd]] != -1)
        {
            lastIndex[elements[currSegmentEnd]] = currSegmentEnd;
            UpdateLongestSegment
            continue;
        }
        if (numberOfDiffValues < diffValueLimit)
        {
            numberOfDiffValues++;
            lastIndex[elements[currSegmentEnd]] = currSegmentEnd;
            UpdateLongestSegment
            continue;
        }

        while (lastIndex[elements[currSegmentBegin]] != currSegmentBegin)
        {
            currSegmentBegin++;
        }
        lastIndex[elements[currSegmentBegin]] = -1;
        currSegmentBegin++;
        lastIndex[elements[currSegmentEnd]] = currSegmentEnd;
        UpdateLongestSegment
    }

    return longestSegment;
}

int main()
{
    Input();
    
    pair<int, int> longestSegment = GetLongestSegment();
    printf("%d %d\n", longestSegment.first + 1, longestSegment.second + 1);

    return 0;
}
