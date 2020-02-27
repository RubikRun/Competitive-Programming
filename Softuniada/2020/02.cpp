#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int r = 0;
    while (true)
    {
        for (int k = 4; k >= 1; k--)
        {
            for (int i = 0; i < n; i++)
            {
                if (i % 4 == k % 4)
                {
                    cout << "#";
                }
                else
                {
                    cout << ".";    
                }
            }
            cout << endl;
            r++;
            if (r >= n + n / 2)
            {
                return 0;
            }
        }
    }

    //5->7
    //7->10
    //9->13
    //n + n/2
}