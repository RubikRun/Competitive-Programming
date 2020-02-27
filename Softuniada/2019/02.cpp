#include <iostream>
using namespace std;

void PrintChars(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << c;
    }
}

void PrintTwoChars(char c1, char c2, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << c1 << c2;
    }
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n * 4 + 2; i++)
    {
        if (i < n / 2 || n * 4 + 1 - i < n / 2)
        {
            PrintChars(' ', n);
            PrintChars('#', 3 * n);
            PrintChars(' ', n);
        }
        else if (i == n / 2 || i == n / 2 + n * 2)
        {
            PrintChars('#', n);
            PrintChars(' ', 3 * n);
            PrintChars('#', n);
        }
        else if (i > n / 2 + n * 2 && n * 4 + 1 - i >= n / 2)
        {
            if ((i - n / 2 - n * 2) % 2 == 0)
            {
                PrintChars('#', n);
                PrintTwoChars(' ', '#', (3 * n - 1) / 2);
                cout << ' ';
                PrintChars('#', n);
            }
            else PrintChars('#', 5 * n);
        }
        else
        {
            if ((i - n / 2) % 2 == 0)
            {
                PrintChars('#', n);
                cout << ' ';
                PrintTwoChars(' ', '#', (3 * n - 3) / 2);
                cout << "  ";
                PrintChars('#', n);
            }
            else
            {
                PrintChars('#', n);
                PrintTwoChars(' ', '#', (3 * n - 1) / 2);
                cout << ' ';
                PrintChars('#', n);
            }
        }
        cout << endl;
    }
}