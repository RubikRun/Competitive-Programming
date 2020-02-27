//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MaxNumberOfPuncts 1000

int main()
{
    int numberOfPuncts;
    scanf("%d", &numberOfPuncts);

    if (numberOfPuncts <= 3)
    {
        int punctPrice, minPunctPrice;
        scanf("%d", &minPunctPrice);
        for (int punctIndex = 1; punctIndex < numberOfPuncts; punctIndex++)
        {
            scanf("%d", &punctPrice);
            if (punctPrice < minPunctPrice)
            {
                minPunctPrice = punctPrice;
            }
        }

        printf("%d\n", minPunctPrice);

        return 0;
    }

    int punctPrices[MaxNumberOfPuncts + 1];
    punctPrices[0] = 0;
    for (int punctIndex = 1; punctIndex <= numberOfPuncts; punctIndex++)
    {
        scanf("%d", &punctPrices[punctIndex]);
    }

    int minSum[MaxNumberOfPuncts + 1];
    minSum[numberOfPuncts] = 0;
    minSum[numberOfPuncts - 1] = 0;
    minSum[numberOfPuncts - 2] = 0;
    for (int punctIndex = numberOfPuncts - 3; punctIndex >= 0; punctIndex--)
    {
        minSum[punctIndex] = min(min(punctPrices[punctIndex + 1] + minSum[punctIndex + 1],
                                 punctPrices[punctIndex + 2] + minSum[punctIndex + 2]),
                                 punctPrices[punctIndex + 3] + minSum[punctIndex + 3]);
    }

    printf("%d\n", minSum[0]);

    return 0;
}