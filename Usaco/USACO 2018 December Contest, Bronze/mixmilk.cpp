/*
ID: borisd22
TASK: mixmilk
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define NumberOfBuckets 3
#define NumberOfPours 100

ifstream fin ("mixmilk.in");
ofstream fout ("mixmilk.out");

int capacity[NumberOfBuckets];
int milk[NumberOfBuckets];

void Input()
{
    for (int i = 0; i < NumberOfBuckets; i++)
    {
        Read >> capacity[i] >> milk[i];
    }
}

void Pour(int a, int b)
{
    int pouredMilk = min(milk[a], capacity[b] - milk[b]);
    milk[a] -= pouredMilk;
    milk[b] += pouredMilk;
}

void DoPours()
{
    for (int i = 0; i < NumberOfPours; i++)
    {
        Pour(i % 3, (i + 1) % 3);
    }
}

int main()
{
    Input();

    DoPours();
    for (int i = 0; i < NumberOfBuckets; i++)
    {
        Write << milk[i] << endl;
    }

    return 0;
}
