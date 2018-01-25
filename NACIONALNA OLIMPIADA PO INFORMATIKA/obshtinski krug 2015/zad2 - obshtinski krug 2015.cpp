#include <stdio.h>
#include <algorithm>
#define maxv 999
#define maxi 999999
using namespace std;
int main()
{
    unsigned n, vti[maxv+1], s, xei=maxi, xev;
    for (int i=0; i<maxv+1; i++) vti[i]=0;

    scanf("%u", &n);
    for (unsigned i=1; i<=n; i++)
    {
        scanf("%u", &xev);
        if (vti[xev]==0) vti[xev]=i;
    }
    scanf("%u", &s);

    for (int i=s-maxv; i<=s/2; i++)
    {
        if (vti[i]==0 || vti[s-i]==0 || min(vti[i], vti[s-i])>=xei) continue;
        xev=i;
        if (vti[s-i]<xei) xev=s-i;
        xei=vti[xev];
    }

    if (xei==maxi) printf("0 0\n");
    else printf("%u %u\n", min(xei, vti[s-xev]), max(xei, vti[s-xev]));
}
