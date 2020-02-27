//Това е авторското решение и не работи правилно
//Tova e avtorskoto reshenie i ne raboti pravilno

#include <iostream>
#include <string.h>
using namespace std;
char A[64];
int n;
char Mul(char a, char b)
{char c=a-'A',d=b-'A';
    return 'A'+(c^d);
}
char *mulWords(const char *a, const char *b,char *c)
{
    char *r=c;
    while (*a) *r++=Mul(*a++,*b++);
    *r=0;
    return c;
}
bool nextWord(const char *a,char *b)
{int len=strlen(a);
    b[len--]=0;
    while (len>=0 && a[len]=='D') b[len--]='A';
    if (len<0) return false;
    b[len]=a[len--]+1;
    while (len>=0) b[len]=a[len--];
    return true;
}

bool get4(int x2,int a2, int &t1, int &t2, int &t3, int &t4)
{for (t1=0;t1<8;t1++) if (t1!=a2)
            for (t2=t1+1;t2<8;t2++) if (t2!=a2)
                    for (t3=t2+1;t3<8;t3++) if (t3!=a2)
                            for (t4=t3+1;t4<8;t4++) if (t4!=a2)
                                {
                                    if((x2^t1^t2^t3^t4)==a2) return true;
                                    if (a2!=15)
                                    {t4=15;
                                        if ((x2^t1^t2^t3^t4)==a2) return true;
                                    }
                                }
    return false;
}

void solve(int n)
{
    char a[64],b[64];
    int len=strlen(A);
    int i,x2,t1,t2,t3,t4,a2;
    memset(a,'A',len);
    a[len]=0;
    strcpy(b,a);
    *a='C';
    for (i=0;i<n-4;i++)
    {if (strcmp(a,A))
        {cout<<a<<endl;
            mulWords(b,a,b);
        }
        else i--;
        nextWord(a,a);
    }
    x2=4*(b[0]-'A')+b[1]-'A';
    a2=4*(A[0]-'A')+A[1]-'A';
    if (!get4(x2,a2,t1,t2,t3,t4))
    {
        t1=1;t2=4;t3=5;t4=15;
    }
    mulWords(b,A,b);
    b[1]='A'+t1%4;
    b[0]='A'+t1/4;
    cout<<b<<endl;
    memset(b,'A',len);
    b[1]='A'+t2%4;
    b[0]='A'+t2/4;
    cout<<b<<endl;
    memset(b,'D',len);
    if (!strcmp(b,A)) b[len-1]='C';
    b[1]='A'+t3%4;
    b[0]='A'+t3/4;
    cout<<b<<endl;
    b[1]='A'+t4%4;
    b[0]='A'+t4/4;
    cout<<b<<endl;
}

int main (void)
{
    cin>>A;
    cin>>n;
    solve(n);
    return 0;
}