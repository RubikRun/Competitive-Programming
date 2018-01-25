#include <stdio.h>
#define MAXN 200000
using namespace std;
int main()
{
    unsigned n, p[MAXN];
    scanf("%u", &n);
    for (unsigned i=0; i<n; i++) scanf("%u", &p[i]);
    unsigned x, y, a=n-1, b=0, t;
    for (unsigned i=0; i<n; i++)
    {
        t = 0;
        for (unsigned j=i+1; j<n; j++) t+=(p[j] >= j);
        x = p[i] + t;
        if (x < a) a = x;
        t = 0;
        for (unsigned j=i+1; j<n; j++) t+=(p[j] > 0);
        y = p[i] + t;
        if (y > b) b = y;
    }
    printf("%u\n%u\n", b, a);
}
