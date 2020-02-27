//checked - 100%

#include <cstdio>
using namespace std;

int GetNumberOfSums(long long n)
{
    long long a = 2;
    long long b = 2 * n;

    int numberOfSums = 0;
    int m = 1;
    while (b > 0)
    {
        if (b % a == 0)
        {
            numberOfSums++;
        }

        a += 2;
        b -= 2 * m;
        m++;
    }

    return numberOfSums;
}

int main()
{
    long long n;
    scanf("%lld", &n);

    int numberOfSums = GetNumberOfSums(n);

    printf("%d\n", numberOfSums);

    return 0;
}