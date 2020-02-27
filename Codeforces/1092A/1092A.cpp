#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n, k;
        cin >> n >> k;

        for (int j = 0; j < k; j++)
        {
            for (int r = 0; r < n / k; r++)
            {
                cout << (char)('a' + j);
            }
        }
        for (int j = 0; j < n % k; j++)
        {
            cout << (char)('a' + j);
        }
        cout << endl;
    }

    return 0;
}
