/*
ID: borisd22
TASK: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("wormhole.out");
ifstream fin ("wormhole.in");

#define MaxNumberOfWormholes 12

struct Point
{
    int x;
    int y;
    int neighbourIndex;
    int nextIndex;
};

bool StuckPairing(Point wormholes[], int numberOfWormholes)
{
    int currentIndex;
    for (int beginIndex = 0; beginIndex < numberOfWormholes; beginIndex++)
    {
        currentIndex = beginIndex;

        while (wormholes[currentIndex].nextIndex != -1)
        {
            currentIndex = wormholes[wormholes[currentIndex].nextIndex].neighbourIndex;
            if (currentIndex == beginIndex)
            {
                return true;
            }
        }
    }

    return false;
}

void AddEdgesAndCountStuckPairings(Point wormholes[], int numberOfWormholes, int& numberOfStuckPairings)
{

    for (int i = 0; i < numberOfWormholes; i++)
    {
        if (wormholes[i].neighbourIndex == -1)
        {
            for (int j = i + 1; j < numberOfWormholes; j++)
            {
                if (wormholes[j].neighbourIndex == -1)
                {
                    wormholes[i].neighbourIndex = j;
                    wormholes[j].neighbourIndex = i;


                    bool allEdgesSet = true;
                    for (int k = 0; k < numberOfWormholes; k++)
                    {
                        if (wormholes[k].neighbourIndex == -1)
                        {
                            allEdgesSet = false;
                            break;
                        }
                    }

                    if (!allEdgesSet)
                    {
                        AddEdgesAndCountStuckPairings(wormholes, numberOfWormholes, numberOfStuckPairings);
                    }
                    else
                    {
                        if (StuckPairing(wormholes, numberOfWormholes))
                        {
                            numberOfStuckPairings++;
                        }
                    }

                    wormholes[i].neighbourIndex = -1;
                    wormholes[j].neighbourIndex = -1;
                }
            }
            break;
        }
    }
}

void FillNexts(Point wormholes[], int numberOfWormholes)
{
    for (int i = 0; i < numberOfWormholes; i++)
    {
        for (int j = 0; j < numberOfWormholes; j++)
        {
            if (wormholes[i].y == wormholes[j].y && wormholes[j].x > wormholes[i].x)
            {
                if (wormholes[i].nextIndex != -1)
                {
                    if (wormholes[j].x < wormholes[wormholes[i].nextIndex].x)
                    {
                        wormholes[i].nextIndex = j;
                    }
                }
                else
                {
                    wormholes[i].nextIndex = j;
                }
            }
        }
    }
}

int main()
{
    int numberOfWormholes;
    fin >> numberOfWormholes;

    Point wormholes[MaxNumberOfWormholes];
    for (int i = 0; i < numberOfWormholes; i++)
    {
        fin >> wormholes[i].x >> wormholes[i].y;
        wormholes[i].neighbourIndex = -1;
        wormholes[i].nextIndex = -1;
    }

    FillNexts(wormholes, numberOfWormholes);

    int numberOfStuckPairings = 0;
    AddEdgesAndCountStuckPairings(wormholes, numberOfWormholes, numberOfStuckPairings);

    fout << numberOfStuckPairings << endl;

    return 0;
}