//checked - 100%

#include <cstdio>

using namespace std;
#define MaxNumberOfHays 1000000

int numberOfHays;

int heights[MaxNumberOfHays];
int steps[MaxNumberOfHays];

int answers[MaxNumberOfHays];

int s[MaxNumberOfHays];
int sl;

void Input()
{
    scanf("%d", &numberOfHays);

    for (int i = 0; i < numberOfHays; i++)
    {
        scanf("%d", &heights[i]);
    }
    for (int i = 0; i < numberOfHays; i++)
    {
        scanf("%d", &steps[i]);
    }
}

void Solve()
{
    sl = 0;
    for (int i = numberOfHays - 1; i >= 0; i--)
    {
        while (sl > 0 && heights[i] >= heights[s[sl - 1]])
        {
            sl--;
        }
        answers[i] = (steps[i] <= sl) ? s[sl - steps[i]] : -1;
        s[sl++] = i;
    }
}

void Output()
{
    for (int i = 0; i < numberOfHays; i++)
    {
        printf("%d", (answers[i] == -1) ? -1 : heights[answers[i]]);
        if (i < numberOfHays - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}

int main()
{
    Input();
    Solve();
    Output();

    return 0;
}
