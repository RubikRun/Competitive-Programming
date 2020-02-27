#include <iostream>
using namespace std;

#define MAXN 1005

int main()
{
    int n;
    cin >> n;

    int a[2][MAXN];
    for (int i = 0; i < n; i++)
    {
        a[0][i] = i + 1;
        a[1][i] = i + 1;
    }
    int currA = 0, nextA = 1;

    int x;
    while (cin >> x)
    {
        int l = 0, r = x, ai = 0;

        while (l < x && r < n)
        {
            a[nextA][ai++] = a[currA][l++];
            a[nextA][ai++] = a[currA][r++];
        }
        while (l < x)
        {
            a[nextA][ai++] = a[currA][l++];
        }
        while (r < n)
        {
            a[nextA][ai++] = a[currA][r++];
        }
        currA = (currA + 1) % 2;
        nextA = (nextA + 1) % 2;
    }

    for (int i = 0; i < n; i++)
    {
        cout << a[currA][i] << " ";
    }
    cout << endl;

    return 0;
}