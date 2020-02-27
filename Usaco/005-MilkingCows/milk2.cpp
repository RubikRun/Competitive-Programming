/*
ID: borisd22
TASK: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

ofstream fout ("milk2.out");
ifstream fin ("milk2.in");

#define MaxNumberOfFarmers 5000

struct Farmer
{
    int begin;
    int end;
};

bool CompareFarmers(Farmer farmer1, Farmer farmer2)
{
    return farmer1.begin < farmer2.begin;
}

void DeleteFarmer(int farmerIndex, Farmer farmers[], int& numberOfFarmers)
{
    for (int nextFarmerIndex = farmerIndex + 1; nextFarmerIndex < numberOfFarmers; nextFarmerIndex++)
    {
        farmers[nextFarmerIndex - 1] = farmers[nextFarmerIndex];
    }

    numberOfFarmers--;
}

void MakeFarmersNonOverlaping(Farmer farmers[], int& numberOfFarmers)
{
    int notFinishedFarmerIndex = -1;

    for (int farmerIndex = 0; farmerIndex < numberOfFarmers; farmerIndex++)
    {
        if (notFinishedFarmerIndex == -1 || farmers[farmerIndex].begin > farmers[notFinishedFarmerIndex].end)
        {
            notFinishedFarmerIndex = farmerIndex;
            continue;
        }

        farmers[notFinishedFarmerIndex].end = max(farmers[notFinishedFarmerIndex].end, farmers[farmerIndex].end);
        DeleteFarmer(farmerIndex--, farmers, numberOfFarmers);
    }
}

int LongestMilkingTime(Farmer farmers[], int numberOfFarmers)
{
    int longestMilkingTime = 0;
    for (int farmerIndex = 0; farmerIndex < numberOfFarmers; farmerIndex++)
    {
        longestMilkingTime = max(farmers[farmerIndex].end - farmers[farmerIndex].begin, longestMilkingTime);
    }

    return longestMilkingTime;
}

int LongestFreeTime(Farmer farmers[], int numberOfFarmers)
{
    if (numberOfFarmers < 2)
    {
        return 0;
    }

    int longestFreeTime = farmers[1].begin - farmers[0].end;
    for (int farmerIndex = 2; farmerIndex < numberOfFarmers; farmerIndex++)
    {
        longestFreeTime = max(farmers[farmerIndex].begin - farmers[farmerIndex-1].end, longestFreeTime);
    }

    return longestFreeTime;
}

int main()
{
    int numberOfFarmers;
    fin >> numberOfFarmers;

    Farmer farmers[MaxNumberOfFarmers];
    for (int farmerIndex = 0; farmerIndex < numberOfFarmers; farmerIndex++)
    {
        fin >> farmers[farmerIndex].begin;
        fin >> farmers[farmerIndex].end;
    }

    sort(farmers, farmers + numberOfFarmers, CompareFarmers);

    MakeFarmersNonOverlaping(farmers, numberOfFarmers);

    int longestMilkingTime = LongestMilkingTime(farmers, numberOfFarmers);
    int longestFreeTime = LongestFreeTime(farmers, numberOfFarmers);
    fout << longestMilkingTime << " " << longestFreeTime << endl;

    return 0;
}