//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 200000

int main()
{
    int n;
    scanf("%d", &n);

    int a[MAXN], b[MAXN] = {0};
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        if (a[i] > 0)
        {
            x = max(x + 1, a[i]);
            b[0] += (a[i] == i);
        }
    }

    int t = b[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] == i)
        {
            t--;
        }
        b[i] = t;
    }

    int y = a[0] + b[0];
    for (int i = 1; i < n; i++)
    {
        y = min(y, a[i] + b[i]);
    }

    printf("%d\n", x);
    printf("%d\n", y);

    return 0;
}