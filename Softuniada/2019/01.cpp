#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int d[3];
    cin >> d[0] >> d[1] >> d[2];
    int s = d[0] + d[1] + d[2];
    if (s == 0)
    {
        cout << "No digitivision possible." << endl;
        return 0;
    }

    sort(d, d + 3);
    do
    {
        if (d[0] != 0 && (d[0] * 100 + d[1] * 10 + d[2]) % s == 0)
        {
            cout << "Digitivision successful!" << endl;
            return 0;
        }
    } while (next_permutation(d, d + 3));

    cout << "No digitivision possible." << endl;
    return 0;
}