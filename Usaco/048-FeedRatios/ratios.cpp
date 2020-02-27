/*
ID: borisd22
TASK: ratios
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;
#define Read fin
#define Write fout

ifstream fin ("ratios.in");
ofstream fout ("ratios.out");

int main()
{
    int x[3], a[3], b[3], c[3];
    Read >> x[0] >> x[1] >> x[2];
    Read >> a[0] >> a[1] >> a[2];
    Read >> b[0] >> b[1] >> b[2];
    Read >> c[0] >> c[1] >> c[2];

    vector<int> answer = {100, 100, 100, -1};
    for (int af = 0; af < 100; af++)
    {
        for (int bf = 0; bf < 100; bf++)
        {
            for (int cf = 0; cf < 100; cf++)
            {
                if (af + bf + cf >= answer[0] + answer[1] + answer[2])
                {
                    continue;
                }
                for (int xf = 1; xf < 100; xf++)
                {
                    bool holds = true;
                    for (int i = 0; i < 3; i++)
                    {
                        if (af * a[i] + bf * b[i] + cf * c[i] != xf * x[i])
                        {
                            holds = false;
                            break;
                        }
                    }
                    if (holds)
                    {
                        answer = {af, bf, cf, xf};
                    }
                }
            }
        }
    }

    if (answer[0] == 100)
    {
        Write << "NONE" << endl;
    }
    else
    {
        Write << answer[0] << " " << answer[1] << " " << answer[2] << " " << answer[3] << endl;
    }

    return 0;
}
