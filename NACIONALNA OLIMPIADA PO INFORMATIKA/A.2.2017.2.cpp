//checked - 100%

#include <cstdio>
#include <cstring>

using namespace std;
#define MAXN 10000
#define MAXD 1000

char digits[MAXN];
long long tab[MAXN][MAXD];

int n, d;
long long m;

int main()
{
    scanf("%s", digits);
    n = strlen(digits);
    scanf("%d %lld", &d, &m);

    for (int i = 0; i < d; i++)
    {
        tab[0][i] = 0;
    }
    tab[0][(digits[0] - '0') % d] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            tab[i][j] = tab[i - 1][j];
        }

        for (int j = 0; j < d; j++)
        {
            tab[i][(j * 10 + (digits[i] - '0')) % d] = (tab[i][(j * 10 + (digits[i] - '0')) % d] + tab[i - 1][j]) % m;
        }

        tab[i][(digits[i] - '0') % d] = (tab[i][(digits[i] - '0') % d] + 1) % m;
    }

    printf("%lld\n", tab[n - 1][0]);

    return 0;
}
