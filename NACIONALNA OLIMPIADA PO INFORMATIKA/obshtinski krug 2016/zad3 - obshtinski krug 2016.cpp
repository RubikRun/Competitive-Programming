#include <stdio.h>
#include <algorithm>
#define maxl 61
using namespace std;

int intni(char c){if (c=='?') return -1; return (int)c-(int)'0';}
char charni(int n){if (n==-1) return '?'; if (n==0) return '0'; if (n==1) return '1';}
int main()
{
    char inp1[maxl], inp2[maxl], oup[maxl];
    int al=0, bl=0, a[maxl], b[maxl], c=0, e;
    scanf("%s", &inp1);
    scanf("%s", &inp2);

    while(inp1[al]!='\0') al++;
    while(inp2[bl]!='\0') bl++;

    for (e=0; e<=maxl-al; e++) a[e]=0;
    e=al-1;
    while(e>=0)
    {
        a[maxl-al+e]=intni(inp1[e]);
        e--;
    }
    for (e=0; e<=maxl-bl; e++) b[e]=0;
    e=bl-1;
    while(e>=0)
    {
        b[maxl-bl+e]=intni(inp2[e]);
        e--;
    }

    e=maxl-1;
    while(e >= 0)
    {
        if (a[e]==-1 || b[e]==-1 || c==-1) oup[e]='?';
        else
        {
            oup[e]=charni((a[e]+b[e]+c)%2);
            c=(a[e]+b[e]+c)/2;
            e--;
            continue;
        }
        if (e==maxl-1-max(al, bl)) break;

        if (a[e]==-1 && b[e]!=-1 && c!=-1 && (b[e]+c)%2==0) c=(b[e]+c)/2;
        else if (a[e]!=-1 && b[e]==-1 && c!=-1 && (a[e]+c)%2==0) c=(a[e]+c)/2;
        else if (a[e]!=-1 && b[e]!=-1 && c==-1 && (a[e]+b[e])%2==0) c=(a[e]+b[e])/2;
        else c=-1;

        e--;
    }

    while (e<maxl) printf("%c", oup[e++]);
}

