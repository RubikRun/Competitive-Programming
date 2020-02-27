//checked - 100%

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct Cage
{
    int row, col;
    int numberOfMice;
    int neighbourSum;
};

void AddMice(int row, int col, int numberOfMice, vector<Cage>& cages)
{
    for (int i = 0; i < cages.size(); i++)
    {
        if (cages[i].row == row && cages[i].col == col)
        {
            cages[i].numberOfMice += numberOfMice;
            return;
        }
    }

    cages.push_back({row, col, numberOfMice, 0});
}

void AddCageIfFree(int row, int col, vector<Cage>& cages, vector<Cage>& freeCages)
{
    for (int i = 0; i < cages.size(); i++)
    {
        if (cages[i].row == row && cages[i].col == col)
        {
            return;
        }
    }

    for (int i = 0; i < freeCages.size(); i++)
    {
        if (freeCages[i].row == row && freeCages[i].col == col)
        {
            return;
        }
    }

    freeCages.push_back({row, col, 0, 0});
}

vector<Cage> GetFreeCages(vector<Cage>& cages)
{
    vector<Cage> freeCages;

    for (int i = 0; i < cages.size(); i++)
    {
        AddCageIfFree(cages[i].row, cages[i].col - 1, cages, freeCages);
        AddCageIfFree(cages[i].row, cages[i].col + 1, cages, freeCages);
        AddCageIfFree(cages[i].row - 1, cages[i].col, cages, freeCages);
        AddCageIfFree(cages[i].row + 1, cages[i].col, cages, freeCages);
    }

    for (int i = 0; i < freeCages.size(); i++)
    {
        for (int j = 0; j < cages.size(); j++)
        {
            if (abs(freeCages[i].row - cages[j].row) + abs(freeCages[i].col - cages[j].col) == 1)
            {
                freeCages[i].neighbourSum += cages[j].numberOfMice;
            }
        }
    }

    return freeCages;
}

int main()
{
    vector<Cage> cages;

    int numberOfCages;
    scanf("%d", &numberOfCages);

    int row, col, numberOfMice;
    for (int i = 0; i < numberOfCages; i++)
    {
        scanf("%d %d %d", &row, &col, &numberOfMice);
        AddMice(row, col, numberOfMice, cages);
    }


    vector<Cage> freeCages = GetFreeCages(cages);

    int maxFreeCageNeighbourSum = 0;
    for (int i = 0; i < freeCages.size(); i++)
    {
        maxFreeCageNeighbourSum = max(maxFreeCageNeighbourSum, freeCages[i].neighbourSum);
    }

    printf("%d\n", maxFreeCageNeighbourSum);

    return 0;
}