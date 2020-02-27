/*
ID: borisd22
TASK: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ofstream fout ("beads.out");
ifstream fin ("beads.in");

#define MaxNumberOfBeads 350

bool TryEasyWin(char beads[], int numberOfBeads)
{
    char color = 'u';

    for (int beadIndex = 0; beadIndex < numberOfBeads; beadIndex++)
    {
        if (color == 'u' && beads[beadIndex] != 'w')
        {
            color = beads[beadIndex];
        }
        if (color != 'u' && (beads[beadIndex] != 'w' && beads[beadIndex] != color))
        {
            return false;
        }
    }

    fout << numberOfBeads << endl;
    return true;
}

void Move(int& you, int direction, int colorChangesAllowed, char beads[], int numberOfBeads)
{
#define StepBack you = (you == 0) ? numberOfBeads - 1 : you - 1;
#define StepForward you = (you == numberOfBeads - 1) ? 0 : you + 1;

    char color = (beads[you] == 'w') ? 'u' : beads[you];
    while (true)
    {
        if (direction == -1)
        {
            StepBack
        }
        else
        {
            StepForward
        }
        if (beads[you] == 'w')
        {
            continue;
        }
        if (beads[you] != color)
        {
            if (color != 'u')
            {
                if (colorChangesAllowed == 0)
                {
                    if (direction == -1)
                    {
                        StepForward
                    }
                    else
                    {
                        StepBack
                    }
                    return;
                }
                colorChangesAllowed--;
            }
            color = beads[you];
        }

    }
}

int main()
{
    int numberOfBeads;
    fin >> numberOfBeads;
    char beads[MaxNumberOfBeads];
    fin >> beads;

    if (TryEasyWin(beads, numberOfBeads))
    {
        return 0;
    }

    int you = 0, youPrev;
    Move(you, -1, 0, beads, numberOfBeads);
    int startPoint = you;
    int currentIntervalLen, maxIntervalLen = 0;

    do
    {
        youPrev = you;
        Move(you, 1, 1, beads, numberOfBeads);
        currentIntervalLen = you - youPrev;
        if (currentIntervalLen < 0)
        {
            currentIntervalLen += numberOfBeads;
        }
        currentIntervalLen++;
        if (currentIntervalLen > maxIntervalLen)
        {
            maxIntervalLen = currentIntervalLen;
        }
        Move(you, -1, 0, beads, numberOfBeads);
    } while (you != startPoint);

    fout << maxIntervalLen << endl;

    return 0;
}