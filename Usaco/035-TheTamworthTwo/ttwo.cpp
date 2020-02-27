/*
ID: borisd22
TASK: ttwo
LANG: C++
*/

#include <fstream>

using namespace std;

ifstream fin ("ttwo.in");
ofstream fout ("ttwo.out");

#define MatrixSize 10
#define MaxMinutes 160000

char matrix[MatrixSize + 1][MatrixSize + 1];

struct Position
{
    int row;
    int col;
};

struct Direction
{
    int deltaRow;
    int deltaCol;
};

Position farmer, cow;
Direction farmerDirection, cowDirection;

bool CoordinateOutOfMatrix(int coordinate)
{
    return (coordinate < 0 || coordinate >= MatrixSize);
}

Direction GetNextDirection(Direction& direction)
{
    Direction nextDirection;

    if (direction.deltaRow == 0)
    {
        nextDirection.deltaRow = direction.deltaCol;
        nextDirection.deltaCol = 0;
    }
    else
    {
        nextDirection.deltaRow = 0;
        nextDirection.deltaCol = -direction.deltaRow;
    }

    return nextDirection;
}

void Input()
{
    for (int i = 0; i < MatrixSize; i++)
    {
        fin >> matrix[i];
        for (int j = 0; j < MatrixSize; j++)
        {
            if (matrix[i][j] == 'F')
            {
                matrix[i][j] = '.';
                farmer.row = i;
                farmer.col = j;
            }
            else if (matrix[i][j] == 'C')
            {
                matrix[i][j] = '.';
                cow.row = i;
                cow.col = j;
            }
        }
    }
}

void InitDirections()
{
    farmerDirection = {-1, 0};
    cowDirection = {-1, 0};
}

void PassMinute()
{
    if (CoordinateOutOfMatrix(farmer.row + farmerDirection.deltaRow) ||
    CoordinateOutOfMatrix(farmer.col + farmerDirection.deltaCol) ||
    matrix[farmer.row + farmerDirection.deltaRow][farmer.col + farmerDirection.deltaCol] == '*')
    {
        farmerDirection = GetNextDirection(farmerDirection);
    }
    else
    {
        farmer.row += farmerDirection.deltaRow;
        farmer.col += farmerDirection.deltaCol;
    }


    if (CoordinateOutOfMatrix(cow.row + cowDirection.deltaRow) ||
    CoordinateOutOfMatrix(cow.col + cowDirection.deltaCol) ||
    matrix[cow.row + cowDirection.deltaRow][cow.col + cowDirection.deltaCol] == '*')
    {
        cowDirection = GetNextDirection(cowDirection);
    }
    else
    {
        cow.row += cowDirection.deltaRow;
        cow.col += cowDirection.deltaCol;
    }
}

int GetMinutes()
{
    for (int minutes = 1; minutes <= MaxMinutes; minutes++)
    {
        PassMinute();
        if (farmer.row == cow.row && farmer.col == cow.col)
        {
            return minutes;
        }
    }

    return 0;
}



int main()
{
    Input();
    InitDirections();

    int minutes = GetMinutes();
    fout << minutes << endl;

    return 0;
}