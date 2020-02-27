/*
ID: borisd22
TASK: holstein
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("holstein.out");
ifstream fin ("holstein.in");

#define MaxNumberOfTypes 25
#define MaxNumberOfFoods 15

bool CombinationIsEnough(vector<int>& combination, int foods[][MaxNumberOfTypes], int needs[], int numberOfNeeds)
{
    int amount[MaxNumberOfTypes];
    for (int i = 0; i < numberOfNeeds; i++)
    {
        amount[i] = 0;
    }

    for (int i = 0; i < combination.size(); i++)
    {
        for (int j = 0; j < numberOfNeeds; j++)
        {
            amount[j] += foods[combination[i]][j];
        }
    }

    for (int i = 0; i < numberOfNeeds; i++)
    {
        if (amount[i] < needs[i])
        {
            return false;
        }
    }

    return true;
}

bool NextCombination(vector<int>& combination, int limit)
{
    if (combination.back() + 1 == limit)
    {
        bool IsLast = true;
        for (int i = 0; i < combination.size() - 1; i++)
        {
            if (combination[i] + 1 != combination[i + 1])
            {
                IsLast = false;
            }
        }

        if (IsLast)
        {
            return false;
        }
    }

    for (int i = (int)combination.size() - 1; i >= 0; i--)
    {
        bool canMove;

        if (i == (int)combination.size() - 1)
        {
            canMove = (combination[i] < limit - 1);
        }
        else
        {
            canMove = (combination[i] + 1 < combination[i + 1]);
        }

        if (canMove)
        {
            combination[i]++;
            for (int j = 1; j <= combination.size() - 1 - i; j++)
            {
                combination[i + j] = combination[i] + j;
            }
            return true;
        }
    }

    return false;
}

vector<int> GetBestCombination(int foods[][MaxNumberOfTypes], int numberOfFoods, int needs[], int numberOfNeeds)
{
    vector<int> combination;

    for (int combinationSize = 1; combinationSize <= numberOfFoods; combinationSize++)
    {
        combination.clear();
        for (int i = 0; i < combinationSize; i++)
        {
            combination.push_back(i);
        }

        do
        {
            if (CombinationIsEnough(combination, foods, needs, numberOfNeeds))
            {
                return combination;
            }
        } while (NextCombination(combination, numberOfFoods));
    }
}

int main()
{
    //input
    int numberOfNeeds;
    fin >> numberOfNeeds;

    int needs[MaxNumberOfTypes];
    for (int i = 0; i < numberOfNeeds; i++)
    {
        fin >> needs[i];
    }

    int numberOfFoods;
    fin >> numberOfFoods;

    int foods[MaxNumberOfFoods][MaxNumberOfTypes];
    for (int i = 0; i < numberOfFoods; i++)
    {
        for (int j = 0; j < numberOfNeeds; j++)
        {
            fin >> foods[i][j];
        }
    }

    //solution
    vector<int> bestCombination = GetBestCombination(foods, numberOfFoods, needs, numberOfNeeds);

    //output
    fout << bestCombination.size() << " ";

    for (int i = 0; i < bestCombination.size() - 1; i++)
    {
        fout << bestCombination[i] + 1 << " ";
    }
    fout << bestCombination.back() + 1 << endl;

    return 0;
}