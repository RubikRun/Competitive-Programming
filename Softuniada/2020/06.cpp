#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100005

int main()
{
    int k, n;
    cin >> k >> n;

    int a[MAXN];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);

    int minDif = a[n - 1] - a[0];
    for (int i = 0; i + k - 1 < n; i++)
    {
        minDif = min(minDif, a[i + k - 1] - a[i]);
    }
    cout << minDif << endl;

    return 0;
}