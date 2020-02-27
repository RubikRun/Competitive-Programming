/*
ID: borisd22
TASK: barn1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ofstream fout ("barn1.out");
ifstream fin ("barn1.in");

#define MaxNumberOfStalls 200

int GetMinNumberOfStallsBlocked(int maxNumberOfBoards, int numberOfStalls, int cows[], int numberOfCows)
{
    sort(cows, cows + numberOfCows);

    int differences[MaxNumberOfStalls];
    int numberOfDifferences = numberOfCows - 1;
    for (int differenceIndex = 0; differenceIndex < numberOfDifferences; differenceIndex++)
    {
        differences[differenceIndex] = cows[differenceIndex + 1] - cows[differenceIndex] - 1;
    }

    sort(differences, differences + numberOfDifferences);

    int numberOfStallsBlocked = numberOfCows;

    for (int differenceIndex = 0; differenceIndex < numberOfCows - maxNumberOfBoards; differenceIndex++)
    {
        numberOfStallsBlocked += differences[differenceIndex];
    }

    return numberOfStallsBlocked;
}

int main()
{
    int maxNumberOfBoards;
    fin >> maxNumberOfBoards;
    int numberOfStalls;
    fin >> numberOfStalls;
    int numberOfCows;
    fin >> numberOfCows;

    int cows[MaxNumberOfStalls];
    for (int cowIndex = 0; cowIndex < numberOfCows; cowIndex++)
    {
        fin >> cows[cowIndex];
        cows[cowIndex]--;
    }

    int numberOfStallsBlocked = GetMinNumberOfStallsBlocked(maxNumberOfBoards, numberOfStalls, cows, numberOfCows);

    fout << numberOfStallsBlocked << endl;

    return 0;
}