/*
ID: borisd22
TASK: ariprog
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>

using namespace std;

ofstream fout ("ariprog.out");
ifstream fin ("ariprog.in");

#define MaxM 250
#define MaxNumberOfValidProgressions 10000

bitset<MaxM * MaxM + MaxM * MaxM> belongsToS;
int n, m;

void FillS()
{
    for (int p = 0; p <= m; p++)
    {
        for (int q = p; q <= m; q++)
        {
            belongsToS[p * p + q * q] = 1;
        }
    }
}

struct Progression
{
    int a;
    int b;
};

bool ProgressionComparator(Progression& pr1, Progression& pr2)
{
    if (pr1.b == pr2.b)
    {
        return pr1.a < pr2.a;
    }
    return pr1.b < pr2.b;
}

bool ProgressionIsValid(Progression pr)
{
    for (int i = 0; i < n; i++)
    {
        if (belongsToS[pr.a + pr.b * i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    fin >> n;
    fin >> m;

    FillS();

    Progression validProgressions[MaxNumberOfValidProgressions + 1];
    int numberOfValidProgressions = 0;

    for (int a = 0; a <= m * m + m * m; a++)
    {
        for (int b = 1; b <= m * m + m * m && a + (n - 1) * b <= m * m + m * m; b++)
        {
            validProgressions[numberOfValidProgressions].a = a;
            validProgressions[numberOfValidProgressions].b = b;

            if (ProgressionIsValid(validProgressions[numberOfValidProgressions]))
            {
                numberOfValidProgressions++;
            }
        }
    }

    if (numberOfValidProgressions == 0)
    {
        fout << "NONE" << endl;
        return 0;
    }

    sort(validProgressions, validProgressions + numberOfValidProgressions, ProgressionComparator);

    for (int i = 0; i < numberOfValidProgressions; i++)
    {
        fout << validProgressions[i].a <<  " " << validProgressions[i].b << endl;
    }

    return 0;
}

