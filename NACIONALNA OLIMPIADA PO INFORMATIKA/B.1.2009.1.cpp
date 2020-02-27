//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxNumberOfRegions 999

int GCD(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = a;
        a = b;
        b = c % b;
    }

    return a;
}

int NextRegion(int currentRegion, int spacing, int numberOfRegions)
{
    currentRegion += spacing;
    if (currentRegion > numberOfRegions)
    {
        return currentRegion - numberOfRegions;
    }
    return currentRegion;
}

int CalcTurnOff(int spacing, int numberOfRegions, int specialRegion)
{
    int turnOff = 0;
    int currentRegion = 1;

    while (currentRegion != specialRegion)
    {
        currentRegion = NextRegion(currentRegion, spacing, numberOfRegions);
        turnOff++;
    }

    return turnOff;
}

int main()
{
    int numberOfRegions, specialRegion;
    scanf("%d%d", &numberOfRegions, &specialRegion);

    int bestSpacing = 1, bestSpacingTurnOff = specialRegion - 1;
    int currentSpacing = 2, currentSpacingTurnOff;
    while (currentSpacing < numberOfRegions)
    {
        if (GCD(currentSpacing, numberOfRegions) == 1)
        {
            currentSpacingTurnOff = CalcTurnOff(currentSpacing, numberOfRegions, specialRegion);
            if (currentSpacingTurnOff > bestSpacingTurnOff)
            {
                bestSpacing = currentSpacing;
                bestSpacingTurnOff = currentSpacingTurnOff;
            }
        }
        currentSpacing++;
    }

    printf("%d\n", bestSpacing);
    return 0;
}