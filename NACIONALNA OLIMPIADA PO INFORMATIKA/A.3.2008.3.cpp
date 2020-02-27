//checked - 40%

#include <iostream>

using namespace std;
#define MaxNumberOfRows 500
#define MaxNumberOfCols 32

struct Cell
{
    bool colored;
    bool social; //has a neighbour cell that is colored
};

Cell cells[MaxNumberOfRows][MaxNumberOfCols];
int numberOfRows;
int numberOfCols;

int numberOfSocialCells;

int numberOfColorings;

int depth;
void ColorCells(int lastCellRow, int lastCellCol)
{
    if (numberOfSocialCells == numberOfRows * numberOfCols)
    {
        numberOfColorings++;
        return;
    }

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            if (i < lastCellRow)
            {
                continue;
            }
            if (i == lastCellRow && j <= lastCellCol)
            {
                continue;
            }
            if (cells[i][j].colored)
            {
                continue;
            }
            if (i < numberOfRows - 1 && cells[i + 1][j].social)
            {
                continue;
            }
            if (i > 0 && cells[i - 1][j].social)
            {
                continue;
            }
            if (j < numberOfCols - 1 && cells[i][j + 1].social)
            {
                continue;
            }
            if (j > 0 && cells[i][j - 1].social)
            {
                continue;
            }

            cells[i][j].colored = true;
            if (i < numberOfRows - 1)
            {
                cells[i + 1][j].social = true;
                numberOfSocialCells++;
            }
            if (i > 0)
            {
                cells[i - 1][j].social = true;
                numberOfSocialCells++;
            }
            if (j < numberOfCols - 1)
            {
                cells[i][j + 1].social = true;
                numberOfSocialCells++;
            }
            if (j > 0)
            {
                cells[i][j - 1].social = true;
                numberOfSocialCells++;
            }

            depth++;
            ColorCells(i, j);
            depth--;

            cells[i][j].colored = false;
            if (i < numberOfRows - 1)
            {
                cells[i + 1][j].social = false;
                numberOfSocialCells--;
            }
            if (i > 0)
            {
                cells[i - 1][j].social = false;
                numberOfSocialCells--;
            }
            if (j < numberOfCols - 1)
            {
                cells[i][j + 1].social = false;
                numberOfSocialCells--;
            }
            if (j > 0)
            {
                cells[i][j - 1].social = false;
                numberOfSocialCells--;
            }
        }
    }
}

int main()
{
    for (numberOfRows = 1; numberOfRows <= 20; numberOfRows++)
    {
        for (numberOfCols = 6; numberOfCols <= 6; numberOfCols++)
        {
            for (int i = 0; i < numberOfRows; i++)
            {
                for (int j = 0; j < numberOfCols; j++)
                {
                    cells[i][j].colored = false;
                    cells[i][j].social = false;
                }
            }
            numberOfSocialCells = 0;

            numberOfColorings = 0;
            depth = 0;
            ColorCells(0, -1);

            cout << numberOfColorings << " ";
        }
        cout << endl;
    }

    return 0;
}
