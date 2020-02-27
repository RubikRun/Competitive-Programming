/*
ID: borisd22
TASK: cowpatibility
LANG: C++
*/

#include <fstream>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfCows 50000
#define NumberOfFavoriteFlavors 5

ifstream fin ("cowpatibility.in");
ofstream fout ("cowpatibility.out");

int cows[MaxNumberOfCows][NumberOfFavoriteFlavors];
int numberOfCows;

void Input()
{
    Read >> numberOfCows;

    for (int i = 0; i < numberOfCows; i++)
    {
        for (int j = 0; j < NumberOfFavoriteFlavors; j++)
        {
            Read >> cows[i][j];
        }
    }
}

bool CowsAreCompatible(int a, int b)
{
    for (int i = 0; i < NumberOfFavoriteFlavors; i++)
    {
        for (int j = 0; j < NumberOfFavoriteFlavors; j++)
        {
            if (cows[a][i] == cows[b][j])
            {
                return true;
            }
        }
    }

    return false;
}

int GetNumberOfNonCompatiblePairs()
{
    int result = 0;

    for (int i = 0; i < numberOfCows - 1; i++)
    {
        for (int j = i + 1; j < numberOfCows; j++)
        {
            if (!CowsAreCompatible(i, j))
            {
                result++;
            }
        }
    }

    return result;
}

int main()
{
    Input();

    Write << GetNumberOfNonCompatiblePairs() << endl;

    return 0;
}
