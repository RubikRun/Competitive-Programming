//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

bool IsMagic(int numbers[])
{
    return (numbers[0]+numbers[1]+numbers[2]==numbers[3]+numbers[4]+numbers[5])
        && (numbers[3]+numbers[4]+numbers[5]==numbers[6]+numbers[7]+numbers[8])
    && (numbers[6]+numbers[7]+numbers[8]==numbers[0]+numbers[3]+numbers[6])
    && (numbers[0]+numbers[3]+numbers[6]==numbers[1]+numbers[4]+numbers[7])
    && (numbers[1]+numbers[4]+numbers[7]==numbers[2]+numbers[5]+numbers[8])
    && (numbers[2]+numbers[5]+numbers[8]==numbers[0]+numbers[4]+numbers[8])
    && (numbers[0]+numbers[4]+numbers[8]==numbers[2]+numbers[4]+numbers[6]);
}

int CountMagicPermutations(int numbers[])
{
    int numberOfMagicPermutations = 0;

    sort(numbers, numbers+9);
    do
    {
        if (IsMagic(numbers))
        {
            numberOfMagicPermutations++;
        }
    } while (next_permutation(numbers, numbers+9));

    return numberOfMagicPermutations;
}

int main()
{
    int numbers[9];
    for (int i = 0; i < 9; i++)
    {
        scanf("%d", &numbers[i]);
    }

    int numberOfMagicPermutations = CountMagicPermutations(numbers);
    printf("%d\n", numberOfMagicPermutations);

    return 0;
}