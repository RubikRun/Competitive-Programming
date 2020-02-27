/*
ID: borisd22
TASK: mooyomooyo
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfRows 100

ifstream fin ("mooyomooyo.in");
ofstream fout ("mooyomooyo.out");

struct Cell
{
    int row;
    int col;
};

int numberOfRows;
const int numberOfCols = 10;
int board[MaxNumberOfRows][numberOfCols];

int regionMinSize;

bool used[MaxNumberOfRows][numberOfCols];

void Input()
{
    Read >> numberOfRows >> regionMinSize;

    for (int i = 0; i < numberOfRows; i++)
    {
        char line[numberOfCols + 1];
        Read >> line;

        for (int j = 0; j < numberOfCols; j++)
        {
            board[i][j] = line[j] - '0';
        }
    }
}

void FillRegionCells(Cell rootCell, vector<Cell>& regionCells)
{
    used[rootCell.row][rootCell.col] = true;
    regionCells.push_back(rootCell);
    int rootCellColor = board[rootCell.row][rootCell.col];

    if (!used[rootCell.row][rootCell.col + 1] && rootCell.col + 1 < numberOfCols && board[rootCell.row][rootCell.col + 1] == rootCellColor)
    {
        FillRegionCells({rootCell.row, rootCell.col + 1}, regionCells);
    }
    if (!used[rootCell.row][rootCell.col - 1] && rootCell.col - 1 >= 0 && board[rootCell.row][rootCell.col - 1] == rootCellColor)
    {
        FillRegionCells({rootCell.row, rootCell.col - 1}, regionCells);
    }
    if (!used[rootCell.row + 1][rootCell.col] && rootCell.row + 1 < numberOfRows && board[rootCell.row + 1][rootCell.col] == rootCellColor)
    {
        FillRegionCells({rootCell.row + 1, rootCell.col}, regionCells);
    }
    if (!used[rootCell.row - 1][rootCell.col] && rootCell.row - 1 >= 0 && board[rootCell.row - 1][rootCell.col] == rootCellColor)
    {
        FillRegionCells({rootCell.row - 1, rootCell.col}, regionCells);
    }
}

bool RemoveRegions()
{
    bool removedSomething = false;

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            used[i][j] = false;
        }
    }

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            if (!used[i][j] && board[i][j] != 0)
            {
                vector<Cell> regionCells;
                FillRegionCells({i, j}, regionCells);

                if (regionCells.size() >= regionMinSize)
                {
                    removedSomething = true;
                    for (int i = 0; i < regionCells.size(); i++)
                    {
                        board[regionCells[i].row][regionCells[i].col] = 0;
                    }
                }
            }
        }
    }

    return removedSomething;
}

void Gravity()
{
    for (int col = 0; col < numberOfCols; col++)
    {
        vector<int> hays;
        for (int row = numberOfRows - 1; row >= 0; row--)
        {
            if (board[row][col] != 0)
            {
                hays.push_back(board[row][col]);
            }
        }

        for (int row = numberOfRows - 1; row >= 0; row--)
        {
            board[row][col] = (numberOfRows - 1 - row < hays.size()) ? hays[numberOfRows - 1 - row] : 0;
        }
    }
}

int main()
{
    Input();

    while (RemoveRegions())
    {
        Gravity();
    }

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            Write << board[i][j];
        }
        Write << endl;
    }

    return 0;
}
