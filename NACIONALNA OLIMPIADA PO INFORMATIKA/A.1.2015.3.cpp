//checked - 100%

#include <cstdio>
using namespace std;
typedef long long ll;
#define dk int k=0; while(n>>k!=0){k++;}
int main()
{
    ll o=1, t=3;
    ll n; scanf("%lld", &n); n++;
    dk
    printf("%lld\n%lld %lld\n",((o<<(k-2))|((n&1)<<(k-3))|((n&((o<<(k-2))-1))>>1))-1,((o<<k)|((n&((o<<(k-2))-1))<<1)|((n&(o<<(k-2)))>>(k-2)))-1,((t<<(k-1))|((n&((o<<(k-2))-1))<<1)|((n&(o<<(k-2)))>>(k-2)))-1);
    return 0;
}