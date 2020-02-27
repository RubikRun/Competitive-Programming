/*
ID: borisd22
TASK: backforth
LANG: C++
*/

#include <fstream>
#include <set>

using namespace std;
#define Read fin
#define Write fout

ifstream fin ("backforth.in");
ofstream fout ("backforth.out");

int buckets[2][10];
set<int> readings;

int main()
{
    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < 10; i++)
        {
            Read >> buckets[k][i];
        }
    }

    readings.insert(0);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            readings.insert(-buckets[0][i] + buckets[1][j]);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (j == i) continue;
            for (int x = 0; x < 10; x++)
            {
                for (int y = 0; y < 10; y++)
                {
                    if (y == x) continue;
                    readings.insert(-buckets[0][i] - buckets[0][j] + buckets[1][x] + buckets[1][y]);
                }
            }
        }
    }

    Write << readings.size() << endl;

    return 0;
}
