#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 100

int a[MAXN];
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);

    int r = 0;
    for (int i = 0; i < n; i += 2)
    {
        r += a[i + 1] - a[i];
    }

    cout << r << endl;

    return 0;
}
