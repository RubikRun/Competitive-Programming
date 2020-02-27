/*
ID: borisd22
TASK: preface
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout ("preface.out");
ifstream fin ("preface.in");

vector< pair<char, int> > romanDigitCount;

bool RomanDigitCountComparator(pair<char, int>& a, pair<char, int>& b)
{
    return a.second > b.second;
}

int GetNumberOfI(int n)
{
    n = n % 10;

    if (n <= 3)
    {
        return n;
    }
    else if (n <= 8)
    {
        return abs(n - 5);
    }
    else
    {
        return abs(n - 10);
    }
}

int GetNumberOfV(int n)
{
    n = n % 10;

    return (n >= 4 && n <= 8) ? 1 : 0;
}

int GetNumberOfX(int n)
{
    return GetNumberOfI(n / 10) + (n % 10 == 9);
}

int GetNumberOfL(int n)
{
    return GetNumberOfV(n / 10);
}

int GetNumberOfC(int n)
{
    return GetNumberOfX(n / 10);
}

int GetNumberOfD(int n)
{
    return GetNumberOfV(n / 100);
}

int GetNumberOfM(int n)
{
    return GetNumberOfX(n / 100);
}

void CountRomanDigits(int n)
{
    romanDigitCount = {{'I', 0}, {'V', 0}, {'X', 0}, {'L', 0}, {'C', 0}, {'D', 0}, {'M', 0}};

    for (int i = 1; i <= n; i++)
    {
        romanDigitCount[0].second += GetNumberOfI(i);
        romanDigitCount[1].second += GetNumberOfV(i);
        romanDigitCount[2].second += GetNumberOfX(i);
        romanDigitCount[3].second += GetNumberOfL(i);
        romanDigitCount[4].second += GetNumberOfC(i);
        romanDigitCount[5].second += GetNumberOfD(i);
        romanDigitCount[6].second += GetNumberOfM(i);
    }
}

int main()
{
    int n;
    fin >> n;

    CountRomanDigits(n);

    for (int i = 0; i < romanDigitCount.size() && romanDigitCount[i].second > 0; i++)
    {
        fout << romanDigitCount[i].first << " " << romanDigitCount[i].second << endl;
    }

    return 0;
}