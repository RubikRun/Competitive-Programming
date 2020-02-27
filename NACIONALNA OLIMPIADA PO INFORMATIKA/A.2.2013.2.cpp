//checked - 90%

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define epsilon 0.0001

int main()
{
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    double p = 0, x = 0;
    while (p <= c)
    {
        double q = sqrt(c * c - p * p);

        double m1 = p * p / q / q + 1;
        double m2 = q * q / p / p + 1;

        x = max(x, min(min(sqrt(m1 * a * a), sqrt(m1 * (a - p) * (a - p))), min(sqrt(m2 * b * b), sqrt(m2 * (b - q) * (b - q)))));

        p += epsilon;
    }

    printf("%.2lf\n", x);

    return 0;
}