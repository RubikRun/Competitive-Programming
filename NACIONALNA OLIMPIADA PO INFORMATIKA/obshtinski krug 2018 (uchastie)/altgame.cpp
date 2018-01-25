#include <iostream>
using namespace std;
int a, b, m;

int winner(long long unsigned n)
{
    n%=(a+b);
    if (a<=n) return 1;
    return 2;
}

int main()
{
    cin>>a>>b>>m;

    int r[10];
    long long unsigned n;
    for (int i=0; i<m; i++)
    {
        cin>>n;
        r[i]=winner(n);
    }
    for (int i=0; i<m; i++)
    {
        cout<<r[i]<<endl;
    }
    return 0;
}