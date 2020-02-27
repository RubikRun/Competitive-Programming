#include <iostream>
using namespace std;

int main()
{
    double n, m, x, y;
    int t;
    cin >> n >> m >> x >> y >> t;

    double saved = 0;
    for (int i = 0; i < t; i++)
    {
        saved += n - m;
        n += x;
    }

    if (saved >= y)
    {
        cout << "Have a nice ride!" << endl;
    }
    else
    {
        cout << "Work harder!" << endl;
    }

    return 0;
}