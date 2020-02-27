//checked - 100%

#include <cstdio>

using namespace std;

#define MAXN 500

double a[MAXN];
double bestD[MAXN][MAXN + 1];
double d[MAXN][MAXN];
int n, p;

void InitD()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            d[i][j] = -1.0;
        }
    }
}

double GetD(int x, int y)
{
    if (d[x][y] != -1.0)
    {
        return d[x][y];
    }

    double m = 0;
    for (int i = x; i <= y; i++)
    {
        m += a[i];
    }
    m /= (double) (y - x + 1);

    double sum = 0;
    for (int i = x; i <= y; i++)
    {
        sum += (a[i] - m) * (a[i] - m);
    }

    d[x][y] = sum;
    return sum;
}

void InitBestD()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= p; j++)
        {
            bestD[i][j] = -1.0;
        }
    }
}

double GetBestD(int i, int j)
{
    if (bestD[i][j] != -1.0)
    {
        return bestD[i][j];
    }
    if (j == 1)
    {
        return GetD(0, i);
    }

    for (int k = j - 1; k <= i - 1; k++)
    {
        if (bestD[i][j] == -1.0 || GetBestD(k, j - 1) + GetD(k + 1, i) < bestD[i][j])
        {
            bestD[i][j] = GetBestD(k, j - 1) + GetD(k + 1, i);
        }
    }

    return bestD[i][j];
}

int main()
{
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &a[i]);
    }

    InitD();
    InitBestD();
    printf("%6lf\n", GetBestD(n - 1, p));

    return 0;
}