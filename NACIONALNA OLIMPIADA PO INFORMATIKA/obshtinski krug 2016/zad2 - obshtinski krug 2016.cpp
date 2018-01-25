#include<stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;
unsigned a, b;

double compute(double angle)
{
    double n=sin(angle), m=cos(angle)+1;
    return 2*a*b - (2*m*a*b-n*(a*a+b*b))/(m*m-n*n);
}

int main()
{
    scanf("%u %u", &a, &b);
    if (a < b)
    {
        unsigned t;
        t=a;
        a=b;
        b=t;
    }
    double al=0.00001, mincos=(double)(a*a-b*b)/(a*a+b*b), s2, maxs2=0;

    while(cos(al)>=mincos)
    {
        s2=compute(al);
        if (s2>maxs2) maxs2=s2;
        al += 0.00001;
    }

    printf("%.3f\n", max((double)2*a*b-b*b, maxs2));
}
