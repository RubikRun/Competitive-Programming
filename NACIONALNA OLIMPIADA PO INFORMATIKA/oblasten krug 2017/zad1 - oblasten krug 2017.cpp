#include <stdio.h>
using namespace std;
long long unsigned mul, add, mod, k;

long long unsigned get_max(long long unsigned first, long long unsigned amount)
{
    long long unsigned result=first, current_number=first;
    for (int i=2; i<=amount; i++)
    {
        current_number=(mul*current_number+add)%mod;
        if (current_number>result) result=current_number;
    }
    return result;
}

int main()
{
    long long unsigned n, first, current_max, current_number, sum, oldest;
    scanf("%llu%llu%llu%llu%llu%llu", &n, &k, &first, &mul, &add, &mod);
    current_max=first;
    current_number=first;
    oldest=first;
    sum=first;
    for (long long unsigned i=2; i<=n; i++)
    {
        if (i==mod+1)
        {
            sum *= (n / mod);
            i += mod * (n / mod);
        }
        current_number=(mul*current_number+add)%mod;
        if (i<=k)
        {
            if (current_number>current_max) current_max=current_number;
        }
        else
        {
            if (current_number>current_max) current_max=current_number;
            if (oldest>=current_max) current_max=get_max((mul*oldest+add)%mod, k);
            oldest=(mul*oldest+add)%mod;
        }
        sum+=current_max;
    }
    printf("%llu\n", sum);
    return 0;
}
