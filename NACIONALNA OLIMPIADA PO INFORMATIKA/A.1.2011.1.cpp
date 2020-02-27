//checked - 100%

#include <cstdio>
using namespace std;

#define MaxNumberOfRows 101
#define MaxNumberOfCols 101

char cinema[MaxNumberOfRows][MaxNumberOfCols];
int numberOfRows, numberOfCols;

bool RectangleIsFree(int beginRow, int beginCol, int recRows, int recCols)
{
    for (int row = beginRow; row < beginRow + recRows; row++)
    {
        for (int col = beginCol; col < beginCol + recCols; col++)
        {
            if (cinema[row][col] == '#')
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    scanf("%d %d", &numberOfRows, &numberOfCols);
    int rowsNeeded, colsNeeded;
    scanf("%d %d", &rowsNeeded, &colsNeeded);
    for (int row = 0; row < numberOfRows; row++)
    {
        scanf("%s", cinema[row]);
    }


    int numberOfRectangles = 0;

    for (int row = 0; row <= numberOfRows - rowsNeeded; row++)
    {
        for (int col = 0; col <= numberOfCols - colsNeeded; col++)
        {
            if (RectangleIsFree(row, col, rowsNeeded, colsNeeded))
            {
                numberOfRectangles++;
            }
        }
    }

    printf("%d\n", numberOfRectangles);

    return 0;
}