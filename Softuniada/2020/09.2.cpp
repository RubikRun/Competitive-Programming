#include <iostream>
#include <vector>
using namespace std;

#define COINVALUES 23

long long coinValues[COINVALUES] = {1, 10,
25, 100, 1000, 
2500, 10000, 100000, 
250000, 1000000, 10000000, 
25000000, 100000000, 1000000000, 
2500000000, 10000000000, 100000000000, 
250000000000, 1000000000000, 10000000000000, 
25000000000000, 100000000000000, 1000000000000000};

long long RemoveFirstTwoDigits(long long x)
{
    vector<int> d;
    while (x >= 1000)
    {
        d.push_back(x % 10);
        x /= 10;
    }

    long long result = 0;
    for (int i = d.size() - 1; i >= 0; i--)
    {
        result = result * 10 + d[i];
    }

    return result;
}

int main()
{
    long long p;
    cin >> p;
    
    int x = 0;

    while (p > 0)
    {
        int psp = p;
        while (psp >= 1000)
        {
            psp /= 10;
        }
        int psdp[1000];
        psdp[0] = 0;
        psdp[1] = 1;
        for (int i = 2; i <= psp; i++)
        {
            psdp[i] = 1000;
            for (int j = 0; coinValues[j] <= i; j++)
            {
                psdp[i] = min(psdp[i], psdp[i - coinValues[j]] + 1);
            }
        }
        x += psdp[psp];
        p = RemoveFirstTwoDigits(p);
    }

    cout << x << endl;

    return 0;
}