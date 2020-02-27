#include <cstdio>
#include <algorithm>
using namespace std;

#define MaxArrayLength 29

int main()
{
    int arrayLength, numberOfMinuses;
    scanf("%d%d", &arrayLength, &numberOfMinuses);

    int array[MaxArrayLength];
    for (int index = 0; index < arrayLength; index++)
    {
        scanf("%d", &array[index]);
    }

    sort(array + 1, array + arrayLength);

    int sum = array[0];
    for (int index = 1; index <= numberOfMinuses; index++)
    {
        sum -= array[index];
    }
    for (int index = numberOfMinuses + 1; index < arrayLength; index++)
    {
        sum += array[index];
    }

    printf("%d\n", sum);
    return 0;
}