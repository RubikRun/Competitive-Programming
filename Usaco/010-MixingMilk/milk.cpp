/*
ID: borisd22
TASK: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream fout ("milk.out");
ifstream fin ("milk.in");

#define MaxNumberOfFarmers 5000

struct Farmer
{
    int centsPerUnit;
    int unitsPerDay;
};

bool FarmerCentsComparator(Farmer& farmer1, Farmer& farmer2)
{
    return farmer1.centsPerUnit <= farmer2.centsPerUnit;
}

int GetMinPrice(int unitsNeeded, Farmer farmers[], int numberOfFarmers)
{
    sort(farmers, farmers + numberOfFarmers, FarmerCentsComparator);

    int priceByNow = 0;
    int farmersUsed = 0;

    while (unitsNeeded > 0)
    {
        if (farmers[farmersUsed].unitsPerDay <= unitsNeeded)
        {
            unitsNeeded -= farmers[farmersUsed].unitsPerDay;
            priceByNow += farmers[farmersUsed].unitsPerDay * farmers[farmersUsed].centsPerUnit;
            farmersUsed++;
        }
        else
        {
            priceByNow += unitsNeeded * farmers[farmersUsed].centsPerUnit;
            unitsNeeded = 0;
        }
    }

    return priceByNow;
}

int main()
{
    int unitsNeeded;
    fin >> unitsNeeded;
    int numberOfFarmers;
    fin >> numberOfFarmers;

    Farmer farmers[MaxNumberOfFarmers];
    for (int farmerIndex = 0; farmerIndex < numberOfFarmers; farmerIndex++)
    {
        fin >> farmers[farmerIndex].centsPerUnit;
        fin >> farmers[farmerIndex].unitsPerDay;
    }


    int minPrice = GetMinPrice(unitsNeeded, farmers, numberOfFarmers);

    fout << minPrice << endl;

    return 0;
}