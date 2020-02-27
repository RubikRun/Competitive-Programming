//checked - 100%

#include <cstdio>

using namespace std;

#define MaxElementValue 999

int main()
{
    int indexOfElement[MaxElementValue + 1];
    for (int i = 1; i <= MaxElementValue; i++)
    {
        indexOfElement[i] = 0;
    }

    int numberOfElements;
    scanf("%d", &numberOfElements);

    int currentElement;
    for (int i = 1; i <= numberOfElements; i++)
    {
        scanf("%d", &currentElement);
        if (indexOfElement[currentElement] == 0)
        {
            indexOfElement[currentElement] = i;
        }
    }

    int sum;
    scanf("%d", &sum);

    int firstIndex = 0, secondIndex = 0;
    int firstElement = sum - MaxElementValue, secondElement = MaxElementValue;
    while (secondElement > 0 && firstElement <= MaxElementValue)
    {
        if (indexOfElement[firstElement] != 0 && indexOfElement[secondElement] != 0
        && indexOfElement[firstElement] <= indexOfElement[secondElement]
        && (indexOfElement[firstElement] < firstIndex || firstIndex == 0))
        {
            firstIndex = indexOfElement[firstElement];
            secondIndex = indexOfElement[secondElement];
        }

        firstElement++;
        secondElement--;
    }

    printf("%d %d\n", firstIndex, secondIndex);

    return 0;
}