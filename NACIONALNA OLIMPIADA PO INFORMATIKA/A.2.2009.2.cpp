//checked - 72%
//too slow

#include <cstdio>
#include <set>

using namespace std;

#define MaxNumberOfTerms 19

struct Expression
{
    int value;
    int lastAddend;
};

int numberOfTerms;
int terms[MaxNumberOfTerms];
int operators[MaxNumberOfTerms];
Expression partialExpressions[MaxNumberOfTerms];

void InitState()
{
    for (int i = 0; i < numberOfTerms; i++)
    {
        operators[i] = 0;
        partialExpressions[i].value = (i > 0) ? partialExpressions[i - 1].value + terms[i] : terms[i];
        partialExpressions[i].lastAddend = terms[i];
    }
}

bool NextState()
{
    for (int i = numberOfTerms - 1; i >= 1; i--)
    {
        if (operators[i] < 2)
        {
            operators[i]++;

            if (operators[i] == 1)
            {
                partialExpressions[i].value = partialExpressions[i - 1].value - terms[i];
                partialExpressions[i].lastAddend = -terms[i];
            }
            else
            {
                partialExpressions[i].value = partialExpressions[i - 1].value + (terms[i] - 1) * partialExpressions[i - 1].lastAddend;
                partialExpressions[i].lastAddend = terms[i] * partialExpressions[i - 1].lastAddend;
            }

            for (int j = i + 1; j < numberOfTerms; j++)
            {
                partialExpressions[j].value = partialExpressions[j - 1].value + terms[j];
                partialExpressions[j].lastAddend = terms[j];
            }

            return true;
        }
        else
        {
            operators[i] = 0;
        }
    }

    return false;
}

int GetNumberOfDifferentResults()
{
    set<int> results;

    InitState();
    do
    {
        results.insert(partialExpressions[numberOfTerms - 1].value);
    } while (NextState());

    return (int)results.size();
}


int main()
{
    scanf("%d", &numberOfTerms);
    for (int i = 0; i < numberOfTerms; i++)
    {
        scanf("%d", &terms[i]);
    }

    printf("%d\n", GetNumberOfDifferentResults());

    return 0;
}