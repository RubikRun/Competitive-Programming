//checked - 100%

#include <cstdio>
using namespace std;

#define MaxNumber 3000
#define UnknownValue -1

long long numberOfWays[MaxNumber + 1][MaxNumber + 1];

void InitNumberOfWays(int number)
{
    for (int i = 0; i <= number; i++)
    {
        for (int j = 0; j <= number; j++)
        {
            numberOfWays[i][j] = UnknownValue;
        }
    }
}

long long GetNumberOfWays(int number, int maxAddend)
{
    if (number <= 1)
    {
        numberOfWays[number][maxAddend] = 1;
    }
    if (numberOfWays[number][maxAddend] != UnknownValue)
    {
        return numberOfWays[number][maxAddend];
    }

    numberOfWays[number][maxAddend] = 0;

    int addend = 1;
    while (addend <= maxAddend && addend <= number)
    {
        numberOfWays[number][maxAddend] += GetNumberOfWays(number - addend, addend);
        addend *= 2;
    }

    return numberOfWays[number][maxAddend];
}

int main()
{
    int number;
    scanf("%d", &number);

    InitNumberOfWays(number);
    printf("%lld\n", GetNumberOfWays(number, number));

    return 0;
}