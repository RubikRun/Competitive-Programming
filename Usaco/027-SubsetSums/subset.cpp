/*
ID: borisd22
TASK: subset
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("subset.out");
ifstream fin ("subset.in");

#define MaxLastNumber 39
#define MaxSubsetSum 390

long long GetNumberOfSubsets(int subsetSum, int lastNumber)
{
    long long numberOfSubsets[MaxSubsetSum + 1][MaxLastNumber + 1];

    for (int i = 0; i <= subsetSum; i++)
    {
        for (int j = 0; j <= lastNumber; j++)
        {
            //number of subsets with sum i using first j numbers

            if (i == 0)
            {
                numberOfSubsets[i][j] = 1;
                continue;
            }
            if (j == 0)
            {
                numberOfSubsets[i][j] = 0;
                continue;
            }

            numberOfSubsets[i][j] = numberOfSubsets[i][j - 1];
            if (i >= j)
            {
                numberOfSubsets[i][j] += numberOfSubsets[i - j][j - 1];
            }
        }
    }

    return numberOfSubsets[subsetSum][lastNumber];
}

int main()
{
    int n;
    fin >> n;

    if (n % 4 == 1 || n % 4 == 2)
    {
        fout << 0 << endl;
        return 0;
    }

    int subsetSum = n * (n + 1) / 4;
    long long numberOfSubsets = GetNumberOfSubsets(subsetSum, n);

    fout << numberOfSubsets / 2 << endl;

    return 0;
}