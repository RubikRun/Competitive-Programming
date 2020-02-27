/*
ID: borisd22
TASK: skidesign
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream fout ("skidesign.out");
ifstream fin ("skidesign.in");

#define MaxNumberOfHills 1000

int main()
{
    int numberOfHills;
    fin >> numberOfHills;
    int hills[MaxNumberOfHills];
    for (int i = 0; i < numberOfHills; i++)
    {
        fin >> hills[i];
    }

    sort(hills, hills + numberOfHills);

    int minCost = -1, currCost;
    for (int first = 0; first <= 83; first++)
    {
        currCost = 0;
        for (int hillIndex = 0; hillIndex < numberOfHills; hillIndex++)
        {
            if (hills[hillIndex] < first)
            {
                currCost += (hills[hillIndex] - first) * (hills[hillIndex] - first);
            }
            else if (hills[hillIndex] > first + 17)
            {
                currCost += (hills[hillIndex] - first - 17) * (hills[hillIndex] - first - 17);
            }
        }
        if (currCost < minCost || minCost == -1)
        {
            minCost = currCost;
        }
    }

    fout << minCost << endl;

    return 0;
}