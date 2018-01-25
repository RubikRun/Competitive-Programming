#include<stdio.h>
#include<algorithm>
#define MAXN 100000
using namespace std;
struct el{unsigned va; unsigned in;};
bool compareVa(el a, el b){return a.va<b.va;}
bool compareIn(el a, el b){return a.in<b.in;}
int main()
{
    el r1[MAXN];
    el r2[MAXN];
    el c1[MAXN];
    el c2[MAXN];
    unsigned r1l, r2l, c1l, c2l, i, j, k, w, x;

	printf("%u\n", c1[0]);
    for (i=0; i<5; i++)
    {
        scanf("%u", &r1l);
        for (j=0; j<r1l; j++)
        {
            scanf("%u", &r1[j].va);
            r1[j].in=j;
        }
        scanf("%u", &r2l);
        for (j=0; j<r2l; j++)
        {
            scanf("%u", &r2[j].va);
            r2[j].in=j;
        }
    }
}
