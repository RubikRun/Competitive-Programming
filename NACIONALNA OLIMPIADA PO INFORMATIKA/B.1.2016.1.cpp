//checked - 100%

#include <cstdio>
using namespace std;

#define MaxNumberOfTerms 20000

int main()
{
    int numberOfTerms;
    scanf("%d", &numberOfTerms);

    int terms[MaxNumberOfTerms];
    for (int termIndex = 0; termIndex < numberOfTerms; termIndex++)
    {
        scanf("%d", &terms[termIndex]);
    }

    int maxTerm = terms[0], minTerm = terms[0];
    int firstMinTermIndex = 0, firstMaxTermIndex = 0, lastMinTermIndex = 0, lastMaxTermIndex = 0;
    for (int termIndex = 0; termIndex < numberOfTerms; termIndex++)
    {
        if (terms[termIndex] > maxTerm)
        {
            maxTerm = terms[termIndex];
            firstMaxTermIndex = termIndex;
        }
        if (terms[termIndex] < minTerm)
        {
            minTerm = terms[termIndex];
            firstMinTermIndex = termIndex;
        }

        if (terms[termIndex] == maxTerm)
        {
            lastMaxTermIndex = termIndex;
        }
        if (terms[termIndex] == minTerm)
        {
            lastMinTermIndex = termIndex;
        }
    }

    if (lastMaxTermIndex - firstMinTermIndex > lastMinTermIndex - firstMaxTermIndex)
    {
        printf("%d %d\n", firstMinTermIndex + 1, lastMaxTermIndex + 1);
    }
    else
    {
        printf("%d %d\n", firstMaxTermIndex + 1, lastMinTermIndex + 1);
    }

    return 0;
}
