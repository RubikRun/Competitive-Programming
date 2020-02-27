/*
ID: borisd22
TASK: combo
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("combo.out");
ifstream fin ("combo.in");

int AbsVal(int x)
{
    return max(x, -x);
}

int SL(int n, int p[], int q[])
{
    int sl = 0;

    int s[3] = {1, 1, 1};
    while (s[0] <= n)
    {
        while (s[1] <= n)
        {
            while (s[2] <= n)
            {
                bool b1 = true;
                for (int i = 0; i < 3; i++)
                {
                    if (AbsVal(s[i] - p[i]) <= 2 || AbsVal(s[i] - p[i]) >= n - 2)
                    {
                        continue;
                    }
                    b1 = false;
                }
                bool b2 = true;
                for (int i = 0; i < 3; i++)
                {
                    if (AbsVal(s[i] - q[i]) <= 2 || AbsVal(s[i] - q[i]) >= n - 2)
                    {
                        continue;
                    }
                    b2 = false;
                }

                if (b1 || b2)
                {
                    sl++;
                }
                s[2]++;
            }
            s[2] = 1;
            s[1]++;
        }
        s[1] = 1;
        s[0]++;
    }

    return sl;
}

int main()
{
    int n;
    fin >> n;

    int p[3];
    fin >> p[0] >> p[1] >> p[2];

    int q[3];
    fin >> q[0] >> q[1] >> q[2];

    int sl = SL(n, p, q);

    fout << sl << endl;

    return 0;
}