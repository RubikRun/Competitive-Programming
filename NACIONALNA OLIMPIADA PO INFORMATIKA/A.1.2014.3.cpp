//checked - 100%

#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
    double a, b;
    scanf("%lf %lf", &a, &b);

    if (3 * a <= b)
    {
        printf("0.00\n");
        return 0;
    }

    printf("%.2lf\n", 0.5 * (a + b) * sqrt(a * a - (0.5 * (a - b)) * (0.5 * (a - b))));

    return 0;
}