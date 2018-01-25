#include <stdio.h>
#define MX 99
using namespace std;
int gcd(int a, int b)
{
    int r, i;
    while(b != 0)
    {
      r = a % b;
      a = b;
      b = r;
    }
    if (a>0) return a;
    return -a;
}
int main()
{
    int r=0, n, x1, y1, x2, y2, x, y, g, slopesMap[MX][2*MX-1];
    for (int i=0; i<MX; i++) for (int j=0; j<2*MX-1; j++) if (gcd(i,j-MX+1) == 1) slopesMap[i][j] = 1;

    scanf("%d", &n);
    for (int i=0; i<n; i++)
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1<x2)
        {
            x=x2-x1;
            y=y2-y1;
        }
        else if (x1>x2)
        {
            x=x1-x2;
            y=y1-y2;
        }
        else
        {
            x=0;
            y=1;
        }
        g = gcd(x, y);
        x = x / g;
        y = y / g;
        r+=slopesMap[x][y+MX-1];
        slopesMap[x][y+MX-1]=0;
    }
    printf("%d\n", r);
    return 0;
}
