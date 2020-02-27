/*
ID: borisd22
TASK: prefix
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

ifstream fin ("prefix.in");
ofstream fout("prefix.out");

#define MaxPrimitiveSize 10
#define MaxNumberOfPrimitives 200
#define MaxSequenceSize 200000
#define MaxInputLineSize 76

char primitives[MaxNumberOfPrimitives][MaxPrimitiveSize + 1];
int numberOfPrimitives;
char sequence[MaxSequenceSize + 1];
int sequenceSize;

bool PrimitiveFits(int primitveIndex, int begin)
{
    if (begin + strlen(primitives[primitveIndex]) - 1 >= sequenceSize)
    {
        return false;
    }

    for (int i = 0; i < strlen(primitives[primitveIndex]); i++)
    {
        if (primitives[primitveIndex][i] != sequence[begin + i])
        {
            return false;
        }
    }

    return true;
}

int GetSizeOfLongestPrimitivePrefix()
{
    queue<int> primitiveBegins;
    primitiveBegins.push(0);

    int used[MaxSequenceSize];
    for (int i = 0; i < sequenceSize; i++)
    {
        used[i] = 0;
    }
    used[0] = 1;

    int bestSize = 0;
    while (!primitiveBegins.empty())
    {
        int currentBegin = primitiveBegins.front(); primitiveBegins.pop();

        for (int i = 0; i < numberOfPrimitives; i++)
        {
            if (!used[currentBegin + (int)strlen(primitives[i])] && PrimitiveFits(i, currentBegin))
            {
                primitiveBegins.push(currentBegin + (int)strlen(primitives[i]));
                bestSize = max(bestSize, primitiveBegins.back());
                used[primitiveBegins.back()] = 1;
            }
        }
    }

    return bestSize;
}

void Input()
{
    numberOfPrimitives = 0;
    do
    {
        fin >> primitives[numberOfPrimitives++];
    } while (primitives[numberOfPrimitives - 1][0] != '.');
    numberOfPrimitives--;

    sequenceSize = 0;
    char inputLine[MaxInputLineSize + 1];
    int inputLineSize;
    while (fin >> inputLine)
    {
        inputLineSize = (int)strlen(inputLine);
        for (int i = 0; i < inputLineSize; i++)
        {
            sequence[sequenceSize + i] = inputLine[i];
        }
        sequenceSize += inputLineSize;
    }
    sequence[sequenceSize] = '\0';
}

int main()
{
    Input();

    fout << GetSizeOfLongestPrimitivePrefix() << endl;

    return 0;
}