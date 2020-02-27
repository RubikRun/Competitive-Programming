//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }

    if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3] && a[3] == a[4])
    {
        printf("Impossible\n");
        return 0;
    }

    sort(a, a + 5);

    if ((a[0] == a[1] && a[1] == a[2] && a[2] == a[3]) || (a[1] == a[2] && a[2] == a[3] && a[3] == a[4]))
    {
        printf("Four of a Kind\n");
        return 0;
    }

    if ((a[0] == a[1] && a[2] == a[3] && a[3] == a[4]) || (a[0] == a[1] && a[1] == a[2] && a[3] == a[4]))
    {
        printf("Full House\n");
        return 0;
    }

    if (a[0] + 1 == a[1] && a[1] + 1 == a[2] && a[2] + 1 == a[3] && a[3] + 1 == a[4])
    {
        printf("Straight\n");
        return 0;
    }

    for (int i = 0; i < 3; i++)
    {
        if (a[i] == a[i + 1] && a[i + 1] == a[i + 2])
        {
            printf("Three of a Kind\n");
            return 0;
        }
    }

    if ((a[0] == a[1] && a[2] == a[3]) || (a[0] == a[1] && a[3] == a[4]) || (a[1] == a[2] && a[3] == a[4]))
    {
        printf("Two Pairs\n");
        return 0;
    }

    if ((a[0] == a[1]) || (a[1] == a[2]) || (a[2] == a[3]) || (a[3] == a[4]))
    {
        printf("One Pair\n");
        return 0;
    }

    printf("Nothing\n");

    return 0;
}