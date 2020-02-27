/*
ID: borisd22
TASK: nocows
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ifstream fin ("nocows.in");
ofstream fout ("nocows.out");

#define MaxNumberOfNodes 199
#define MaxHeight 99
#define ModValue 9901

int numberOfTrees[MaxNumberOfNodes + 1][MaxHeight + 1];

void FillNumberOfTrees(int numberOfNodes, int height)
{
    numberOfTrees[0][0] = 1;
    for (int i = 1; i <= numberOfNodes; i++)
    {
        numberOfTrees[i][0] = 0;
    }
    for (int i = 1; i <= height; i++)
    {
        numberOfTrees[0][i] = 0;
    }

    for (int j = 1; j <= height; j++)
    {
        for (int i = 1; i <= numberOfNodes; i++)
        {
            numberOfTrees[i][j] = 0;
            for (int p = 0; p < i / 2; p++)
            {
                int q = i - 1 - p;

                if (p == 0 ^ q == 0)
                {
                    continue;
                }

                numberOfTrees[i][j] = (numberOfTrees[i][j] + numberOfTrees[p][j - 1] * numberOfTrees[q][j - 1]) % ModValue;

                for (int k = j - 2; k >= 0; k--)
                {
                    numberOfTrees[i][j] = (numberOfTrees[i][j] + numberOfTrees[p][k] * numberOfTrees[q][j - 1]) % ModValue;
                    numberOfTrees[i][j] = (numberOfTrees[i][j] + numberOfTrees[p][j - 1] * numberOfTrees[q][k]) % ModValue;
                }
            }
            numberOfTrees[i][j] *= 2;

            if (i % 2 != 0)
            {
                numberOfTrees[i][j] = (numberOfTrees[i][j] + numberOfTrees[i / 2][j - 1] * numberOfTrees[i / 2][j - 1]) % ModValue;

                for (int k = j - 2; k >= 0; k--)
                {
                    numberOfTrees[i][j] = (numberOfTrees[i][j] + numberOfTrees[i / 2][k] * numberOfTrees[i / 2][j - 1]) % ModValue;
                    numberOfTrees[i][j] = (numberOfTrees[i][j] + numberOfTrees[i / 2][j - 1] * numberOfTrees[i / 2][k]) % ModValue;
                }
            }
        }
    }
}

int main()
{
    int numberOfNodes, height;
    fin >> numberOfNodes >> height;

    FillNumberOfTrees(numberOfNodes, height);
    fout << numberOfTrees[numberOfNodes][height] << endl;

    return 0;
}