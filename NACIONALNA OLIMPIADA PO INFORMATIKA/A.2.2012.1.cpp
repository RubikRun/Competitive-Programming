//checked - 100%

#include <cstdio>

using namespace std;

#define MAXN 19
#define llu long long unsigned

int main()
{
    llu x;
    scanf("%llu", &x);

    int n;
    scanf("%d", &n);
    int t[MAXN];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t[i]);
    }

    llu a = 1, b = x * t[0];
    while (a != b)
    {
        llu m = (a + b) / 2;

        llu br = 0;
        for (int i = 0; i < n; i++)
        {
            br += m / t[i];
        }

        if (br < x)
        {
            a = m + 1;
        }
        else
        {
            b = m;
        }
    }

    printf("%llu\n", a);

    return 0;
}