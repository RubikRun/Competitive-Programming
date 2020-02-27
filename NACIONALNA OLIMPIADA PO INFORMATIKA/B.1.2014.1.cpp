//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxSum 50

long long unsigned NumberOfWays(int sum, int maxAddend)
{
    if (sum == 1)
    {
        return 1;
    }

    long long unsigned numberOfWays[MaxSum+1];
    numberOfWays[1] = 1;

    for (int currentSum = 2; currentSum <= sum; currentSum++)
    {
        numberOfWays[currentSum] = 0;
        for (int currentAddend = 1; currentAddend <= min(maxAddend, currentSum); currentAddend++)
        {
            if (currentSum - currentAddend == 0)
            {
                numberOfWays[currentSum]++;
            }
            else
            {
                numberOfWays[currentSum] += numberOfWays[currentSum - currentAddend];
            }
        }
    }

    return numberOfWays[sum];
}

int main()
{
    int sum, maxAddend;
    scanf("%d%d", &sum, &maxAddend);

    printf("%llu\n", NumberOfWays(sum, maxAddend));

    return 0;
}