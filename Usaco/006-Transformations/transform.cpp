/*
ID: borisd22
TASK: transform
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("transform.out");
ifstream fin ("transform.in");

#define MaxMatrixSize 10

/*void PrintMatrix(char matrix[][MaxMatrixSize], int matrixSize)
{
    for (int y = 0; y < matrixSize; y++)
    {
        for (int x = 0; x < matrixSize; x++)
        {
            cout << matrix[y][x];
        }
        cout << endl;
    }

    cout << endl;
}*/

void RotateClockwise(char matrix[][MaxMatrixSize], int matrixSize)
{
    if (matrixSize <= 1)
    {
        return;
    }

    char keeper;
    for (int x = 0; x <= (matrixSize-1) / 2; x++)
    {
        for (int y = 0; y < matrixSize / 2; y++)
        {
            keeper = matrix[y][x];
            matrix[y][x] = matrix[matrixSize-x-1][y];
            matrix[matrixSize-x-1][y] = matrix[matrixSize-y-1][matrixSize-x-1];
            matrix[matrixSize-y-1][matrixSize-x-1] = matrix[x][matrixSize-y-1];
            matrix[x][matrixSize-y-1] = keeper;
        }
    }
}

void FlipHorizontally(char matrix[][MaxMatrixSize], int matrixSize)
{
    char keeper;
    for (int y = 0; y < matrixSize; y++)
    {
        for (int x = 0; x < matrixSize / 2; x++)
        {
            keeper = matrix[y][x];
            matrix[y][x] = matrix[y][matrixSize-1-x];
            matrix[y][matrixSize-1-x] = keeper;
        }
    }
}

bool MatriciesAreTheSame(char firstMatrix[][MaxMatrixSize], char secondMatrix[][MaxMatrixSize], int matrixSize)
{
    for (int y = 0; y < matrixSize; y++)
    {
        for (int x = 0; x < matrixSize; x++)
        {
            if (firstMatrix[y][x] != secondMatrix[y][x])
            {
                return false;
            }
        }
    }

    return true;
}

int ActionApplied(char firstMatrix[][MaxMatrixSize], char secondMatrix[][MaxMatrixSize], int matrixSize) {
    RotateClockwise(firstMatrix, matrixSize);
    if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
        return 1;
    }
    RotateClockwise(firstMatrix, matrixSize);
    if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
        return 2;
    }
    RotateClockwise(firstMatrix, matrixSize);
    if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
        return 3;
    }
    RotateClockwise(firstMatrix, matrixSize);

    FlipHorizontally(firstMatrix, matrixSize);
    if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
        return 4;
    } else {
        RotateClockwise(firstMatrix, matrixSize);
        if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
            return 5;
        }
        RotateClockwise(firstMatrix, matrixSize);
        if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
            return 5;
        }
        RotateClockwise(firstMatrix, matrixSize);
        if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
            return 5;
        }
        RotateClockwise(firstMatrix, matrixSize);
    }
    FlipHorizontally(firstMatrix, matrixSize);

    if (MatriciesAreTheSame(firstMatrix, secondMatrix, matrixSize)) {
        return 6;
    }

    return 7;
}

void ReadMatrix(char matrix[][MaxMatrixSize], int matrixSize)
{
    for (int y = 0; y < matrixSize; y++)
    {
        fin >> matrix[y];
    }
}


int main()
{
    int matrixSize;
    fin >> matrixSize;

    char firstMatrix[MaxMatrixSize][MaxMatrixSize], secondMatrix[MaxMatrixSize][MaxMatrixSize];
    ReadMatrix(firstMatrix, matrixSize);
    ReadMatrix(secondMatrix, matrixSize);

    fout << ActionApplied(firstMatrix, secondMatrix, matrixSize) << endl;

    return 0;
}