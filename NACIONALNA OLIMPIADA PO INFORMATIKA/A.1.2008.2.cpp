#include <cstdio>
#include <cmath>
using namespace std;

const double PI  =3.141592653589793238463;

int GCD(int a, int b)
{
    int t;

    while (b != 0)
    {
        t = a;
        a = b;
        b = t % b;
    }

    return a;
}

int main()
{
    int n, p;
    scanf("%d%d", &n, &p);
    p++;

    if (p > n / 2)
    {
        p = n - p;
    }

    int numberOfSegments = n / GCD(n, p);
    double segmentLength = 2 * sin(PI / n * p);

    printf("%.5lf\n", numberOfSegments * segmentLength);

    return 0;
}