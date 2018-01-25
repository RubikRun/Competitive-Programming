#include <stdio.h>
#define MAXN 100000
using namespace std;
int perm[MAXN];
int possible(int first, int last, int cmin)
{
    if (first>last) return 1;
    if (perm[first]==cmin) return possible(first+1, last, cmin+1);
    int v=perm[first]-1, subFirst=-1, subLast=-1, nmin=perm[first]+1;
    for (int i=first+1; i<=last; i++)
    {
        if (perm[i]==v)
        {
            v--;
            if (subFirst!=-1)
            {
                subLast=i-1;
                if (!possible(subFirst, subLast, nmin)) return 0;
                nmin+=subLast-subFirst+1;
                subFirst=-1;
                subLast=-1;
            }
            if (v==cmin-1) return possible(i+1, last, nmin);
            continue;
        }
        if (perm[i]<v) return 0;
        if (subFirst==-1) subFirst=i;
    }
    return 0;
}
int main()
{
    int n, r[5];
    scanf("%d", &n);
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<n; j++)
        {
            scanf("%d", &perm[j]);
        }
        r[i]=possible(0, n-1, 1);
    }
    for (int i=0; i<5; i++) printf("%d", r[i]);
    printf("\n");
    return 0;
}