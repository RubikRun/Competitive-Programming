/*
ID: borisd22
TASK: convention
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfCows 100000
#define MinTime 0
#define MaxTime 1000000000

ifstream fin ("convention.in");
ofstream fout ("convention.out");

int cows[MaxNumberOfCows];
int numberOfCows;

int numberOfBuses;
int busCapacity;

int minWaitLimit;
int maxWaitLimit;

void Input()
{
    Read >> numberOfCows >> numberOfBuses >> busCapacity;

    minWaitLimit = 0;
    maxWaitLimit = MinTime;
    for (int i = 0; i < numberOfCows; i++)
    {
        Read >> cows[i];
        maxWaitLimit = max(maxWaitLimit, cows[i]);
    }
}

bool Possible(int waitLimit)
{
    int cowA = 0, cowB = 0;

    int busesUsed = 0;
    while (cowA < numberOfCows)
    {
        if (busesUsed >= numberOfBuses)
        {
            return false;
        }
        while (cowB + 1 < numberOfCows && cowB - cowA + 1 < busCapacity && cows[cowB + 1] - cows[cowA] <= waitLimit)
        {
            cowB++;
        }
        busesUsed++;
        cowA = cowB + 1;
    }

    return true;
}

int GetMinWaitLimit()
{
    sort(cows, cows + numberOfCows);

    int first = minWaitLimit, mid, last = maxWaitLimit;

    while (first <= last)
    {
        mid = (first + last) / 2;

        bool A = Possible(mid), B = Possible(mid - 1);
        if (A && !B)
        {
            return mid;
        }

        if (A && B)
        {
            last = mid - 1;
        }
        else
        {
            first = mid + 1;
        }
    }

    return mid;
}

int main()
{
    Input();

    Write << GetMinWaitLimit() << endl;

    return 0;
}
