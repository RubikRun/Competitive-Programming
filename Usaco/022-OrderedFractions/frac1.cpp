/*
ID: borisd22
TASK: frac1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream fout ("frac1.out");
ifstream fin ("frac1.in");

#define MaxQLimit 160

struct Fraction
{
    int p;
    int q;
};

bool CompareFractions(Fraction& f1, Fraction& f2)
{
    return f1.p * f2.q < f2.p * f1.q;
}

Fraction fractions[MaxQLimit * MaxQLimit];
int numberOfFractions;

int GCD(int a, int b)
{
    int t;

    while (b != 0)
    {
        t = a;
        a = b;
        b = t % b;
    }

    return a;
}

void FindFractions(int qLimit)
{
    fractions[0].p = 0;
    fractions[0].q = 1;
    fractions[1].p = 1;
    fractions[1].q = 1;
    numberOfFractions = 2;

    for (int q = 1; q <= qLimit; q++)
    {
        for (int p = 1; p < q; p++)
        {
            if (GCD(p, q) == 1)
            {
                fractions[numberOfFractions].p = p;
                fractions[numberOfFractions].q = q;
                numberOfFractions++;
            }
        }
    }
}

int main()
{
    int qLimit;
    fin >> qLimit;

    FindFractions(qLimit);
    sort(fractions, fractions + numberOfFractions, CompareFractions);

    for (int i = 0; i < numberOfFractions; i++)
    {
        fout << fractions[i].p << "/" << fractions[i].q << endl;
    }

    return 0;
}

