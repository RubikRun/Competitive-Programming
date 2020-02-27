//checked - 100%

#include <cstdio>
using namespace std;

#define MaxNumberOfGames 100

bool FirstWins(int numberOfStones)
{
    return numberOfStones % 3 != 0;
}

int main()
{
    int numberOfGames;
    scanf("%d", &numberOfGames);

    int numbersOfStones[MaxNumberOfGames];
    for (int gameIndex = 0; gameIndex < numberOfGames; gameIndex++)
    {
        scanf("%d", &numbersOfStones[gameIndex]);
    }

    for (int gameIndex = 0; gameIndex < numberOfGames; gameIndex++)
    {
        if (FirstWins(numbersOfStones[gameIndex]))
        {
            printf("1");
        }
        else
        {
            printf("2");
        }
    }
    printf("\n");
    return 0;
}