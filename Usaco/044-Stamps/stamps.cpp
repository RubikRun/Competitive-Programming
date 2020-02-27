/*
ID: borisd22
TASK: stamps
LANG: C++
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfStampValues 50
#define MaxStampValue 10000

ifstream fin ("stamps.in");
ofstream fout ("stamps.out");

int envelopeCapacity;
int numberOfStampValues;

int stampValues[MaxNumberOfStampValues];

vector<int> minStamps;

void Input()
{
    Read >> envelopeCapacity >> numberOfStampValues;

    for (int i = 0; i < numberOfStampValues; i++)
    {
        Read >> stampValues[i];
    }

    sort(stampValues, stampValues + numberOfStampValues);
}

void Output()
{
    minStamps.push_back(0);
    for (int i = 1; true; i++)
    {
        minStamps.push_back(-1);
        if (minStamps.size() > MaxStampValue * 2)
        {
            minStamps.erase(minStamps.begin(), minStamps.begin() + MaxStampValue);
        }

        for (int j = 0; j < numberOfStampValues; j++)
        {
            if (stampValues[j] > i)
            {
                break;
            }
            if (minStamps.back() == -1 || minStamps[minStamps.size() - 1 - stampValues[j]] + 1 < minStamps.back())
            {
                minStamps.back() = minStamps[minStamps.size() - 1 - stampValues[j]] + 1;
            }
        }

        if (minStamps.back() == -1 || minStamps.back() > envelopeCapacity)
        {
            Write << i - 1 << endl;
            return;
        }
    }
}

int main()
{
    Input();
    Output();

    return 0;
}
