//checked - 100%

#include <cstdio>

using namespace std;

#define MaxWantedSum 79

int wantedSum;
int largestBlock;

long long unsigned numOfExpr[MaxWantedSum + 1];

void Input()
{
    scanf("%d", &wantedSum);
    scanf("%d", &largestBlock);
}

void FillTable()
{
    numOfExpr[0] = 1;
    numOfExpr[1] = 0;

    for (int sum = 2; sum <= wantedSum; sum++)
    {
        numOfExpr[sum] = 0;
        for (int lastBlock = 2; lastBlock <= largestBlock; lastBlock++)
        {
            if (lastBlock > sum)
            {
                break;
            }

            numOfExpr[sum] += numOfExpr[sum - lastBlock];
            if (sum % lastBlock == 0)
            {
                numOfExpr[sum] += numOfExpr[sum / lastBlock];
            }
        }
    }
}

int main()
{
    Input();
    FillTable();

    printf("%llu\n", numOfExpr[wantedSum]);

    return 0;
}

