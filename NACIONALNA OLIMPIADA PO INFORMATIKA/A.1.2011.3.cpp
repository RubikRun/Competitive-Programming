//checked - 100%

#include <cstdio>
#include <vector>
using namespace std;

vector<int> GetDivisors(int n)
{
    vector<int> divisors;

    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            divisors.push_back(i);
        }
    }

    int firstHalfSize = divisors.size();
    if (divisors.back() * divisors.back() == n)
    {
        firstHalfSize--;
    }

    for (int i = 0; i < firstHalfSize; i++)
    {
        divisors.push_back(n / divisors[i]);
    }

    return divisors;
}

void Solve()
{
    int n;
    scanf("%d", &n);

    vector<int> nDivisors = GetDivisors(n);

    int p, q;
    int t;
    vector<int> tDivisors;
    int a, b;
    for (int pIndex = 0; pIndex < nDivisors.size(); pIndex++)
    {
        p = nDivisors[pIndex];
        q = n / p;

        t = q - p * p;
        if (t < 0 || t % 3 != 0)
        {
            continue;
        }
        t /= 3;

        tDivisors = GetDivisors(t);
        for (int aIndex = 0; aIndex < tDivisors.size(); aIndex++)
        {
            a = tDivisors[aIndex];
            b = t / a;

            if (p == a - b)
            {
                printf("%d %d\n", a, b);
                return;
            }
        }
    }

    printf("NO\n");
}

int main()
{
    Solve();
    Solve();

    return 0;
}