//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxNumberOfTerms 200000
#define MaxPossibleTerm 1000000000

int main()
{
    int maxId;
    scanf("%d", &maxId);

    int numberOfTerms;
    scanf("%d", &numberOfTerms);
    numberOfTerms *= 2;

    int terms[MaxNumberOfTerms + 1];
    for (int termIndex = 0; termIndex < numberOfTerms; termIndex++)
    {
        scanf("%d", &terms[termIndex]);
    }
    terms[numberOfTerms++] = MaxPossibleTerm + 1;

    int tvMin;
    scanf("%d", &tvMin);


    sort(terms, terms + numberOfTerms);

    int tvs[MaxNumberOfTerms], numberOfTvs = 0;
    int intervalValue = -1, firstIntervalTermIndex = 1;
    for (int termIndex = 0; termIndex < numberOfTerms; termIndex++)
    {
        if (terms[termIndex] != intervalValue)
        {
            if (termIndex - firstIntervalTermIndex >= tvMin)
            {
                tvs[numberOfTvs++] = intervalValue;
            }
            firstIntervalTermIndex = termIndex;
            intervalValue = terms[termIndex];
        }
    }

    printf("%d\n", numberOfTvs);
    for (int tvIndex = 0; tvIndex < numberOfTvs; tvIndex++)
    {
        if (tvIndex == numberOfTvs - 1)
        {
            printf("%d\n", tvs[tvIndex]);
        }
        else
        {
            printf("%d ", tvs[tvIndex]);
        }
    }

    return 0;
}