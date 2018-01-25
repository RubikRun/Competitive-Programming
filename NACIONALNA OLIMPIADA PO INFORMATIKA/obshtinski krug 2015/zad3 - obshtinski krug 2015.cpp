//works 100/100 (tested)
#include <stdio.h>
#include <cmath>
using namespace std;
int main()
{
    unsigned long long n, pw=1, m, p, x1, x2;
    scanf("%llu", &n);
    if (n==1)
    {
        printf("0\n3 5");
        return 0;
    }
    if (n==2)
    {
        printf("0\n4 6");
        return 0;
    }

    unsigned h=0;
    while (n>=pw)
    {
        pw=2*pw+1;
        h++;
    }
    pw=pow(2,h-2);
    m=6*pw-1;

    if (n%2==0)
    {
        p=n/2-1;
        if (n<m) p+=pw;
    }
    else
    {
        p=(n-1)/2;
        if (n>=m) p-=pw;
    }

    if (n<m)
    {
        x1=2*n+1;
        x2=x1+4*pw;
    }
    else
    {
        x1=2*(n+1-2*pw);
        x2=2*(n+1);
    }

    printf("%llu\n%llu %llu", p, x1, x2);
}
