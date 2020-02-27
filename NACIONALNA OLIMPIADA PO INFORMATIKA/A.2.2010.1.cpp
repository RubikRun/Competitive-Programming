//checked - 100%

#include <cstdio>

using namespace std;

int GetNumberOfWays(int n)
{
    int numberOfWays = 0;

    for (int difference = 1; difference * 2 <= n; difference++)
    {
        if (n % (difference * 2) == 0)
        {
            numberOfWays++;
        }
    }

    return numberOfWays;
}

int main()
{
    int n;
    scanf("%d", &n);

    int numberOfWays = GetNumberOfWays(n * 2);
    printf("%d\n", numberOfWays);

    return 0;
}