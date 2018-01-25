#include <stdio.h>
using namespace std;
int main()
{
    unsigned a[6][6][6][6], n, i, j, k, z;
    char x[6*6];
    scanf("%u", &n);
    for (i=0; i<n*n; i++) a[0][0][i%n][i/n]=i;
    for (i=1; i<n; i++) for (j=0; j<n; j++) for (k=0; k<n; k++) a[i][0][k][j]=(a[i-1][0][k][j]+n)%(n*n);
    for (i=1; i<n; i++) for (j=0; j<n; j++) for (k=0; k<n; k++) for (z=0; z<n; z++) a[j][i][z][k]=(a[j][i-1][z][k]+1)%(n*n);
    for (i=0; i<n; i++) scanf("%s", &x[i*n]);
    for (i=0; i<n*n; i++){for (j=0; j<n*n; j++) printf("%c", x[a[j/n][i/n][j%n][i%n]]); printf("\n");}
    return 0;
}
