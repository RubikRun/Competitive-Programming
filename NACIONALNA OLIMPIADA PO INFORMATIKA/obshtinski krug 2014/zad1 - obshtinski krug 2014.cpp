//works 100/100
#include <stdio.h>
using namespace std;
int main()
{
    freopen("nsum.10.in", "r", stdin);
    long long unsigned n;
    scanf("%llu", &n);
    long long unsigned a=2, d=1, r=1;
    while(d<n)
    {
        r+=((n-d)%a==0);
        d+=a++;
    }
    printf("%llu\n", r);
    return 0;
}
