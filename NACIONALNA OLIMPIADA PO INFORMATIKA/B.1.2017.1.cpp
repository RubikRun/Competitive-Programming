//checked - 100%

#include <cstdio>
using namespace std;

#define MaxNumberOfTerms 200000

int GetLongestEqualSumsLen(int terms[], int numberOfTerms)
{
    int firstEnd = 0, lastBegin = numberOfTerms - 1;
    int firstSum = terms[0], lastSum = terms[numberOfTerms - 1];
    int longestEqualSumsLen = 0;

    while (firstEnd < lastBegin)
    {
        if (firstSum == lastSum)
        {
            longestEqualSumsLen = firstEnd - lastBegin + numberOfTerms + 1;
            if (terms[firstEnd + 1]  > terms[lastBegin - 1])
            {
                firstSum += terms[++firstEnd];
            }
            else
            {
                lastSum += terms[--lastBegin];
            }
        }
        else
        {
            if (firstSum > lastSum)
            {
                lastSum += terms[--lastBegin];
            }
            else
            {
                firstSum += terms[++firstEnd];
            }
        }
    }

    return longestEqualSumsLen;
}

int main()
{
    int numberOfTerms;
    scanf("%d", &numberOfTerms);

    int terms[MaxNumberOfTerms];
    for (int termIndex = 0; termIndex < numberOfTerms; termIndex++)
    {
        scanf("%d", &terms[termIndex]);
    }

    int longestEqualSumsLen = GetLongestEqualSumsLen(terms, numberOfTerms);

    printf("%d\n", longestEqualSumsLen);

    return 0;
}