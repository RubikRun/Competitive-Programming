//checked - 100%

#include <cstdio>
#include <queue>
using namespace std;

#define MaxNumberOfRows 99
#define MaxNumberOfCols 99

struct Point
{
    int row;
    int col;
};

void FillTwoDimensionalArrayWithFalse(bool arr[][MaxNumberOfCols], int numberOfRows, int numberOfCols)
{
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int col = 0; col < numberOfCols; col++)
        {
            arr[row][col] = false;
        }
    }
}

void VisitIsland(int nodeRow, int nodeCol, bool isVisited[][MaxNumberOfCols],
                 char picture[][MaxNumberOfCols], int numberOfRows, int numberOfCols)
{
    isVisited[nodeRow][nodeCol] = true;
    queue<Point> waitingPoints;
    waitingPoints.push({nodeRow, nodeCol});

    Point currentPoint, currentNeighbour;
    while(!waitingPoints.empty())
    {
        currentPoint = waitingPoints.front();
        waitingPoints.pop();
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
        {
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
            {
                if ((deltaRow == 0 && deltaCol == 0))
                {
                    continue;
                }
                currentNeighbour = {currentPoint.row + deltaRow, currentPoint.col + deltaCol};
                if (currentNeighbour.row < 0 || currentNeighbour.col < 0 ||
                    currentNeighbour.row >= numberOfRows || currentNeighbour.col >= numberOfCols)
                {
                    continue;
                }

                if (!isVisited[currentNeighbour.row][currentNeighbour.col] && picture[currentNeighbour.row][currentNeighbour.col] == '1')
                {
                    waitingPoints.push(currentNeighbour);
                    isVisited[currentNeighbour.row][currentNeighbour.col] = true;
                }
            }
        }
    }
}

void VisitOuterIsland(bool isVisited[][MaxNumberOfCols], char picture[][MaxNumberOfCols], int numberOfRows, int numberOfCols)
{
    for (int row = 0; row < numberOfRows; row++)
    {
        if (!isVisited[row][0] && picture[row][0] == '1')
        {
            VisitIsland(row, 0, isVisited, picture, numberOfRows, numberOfCols);
        }
        if (!isVisited[row][numberOfCols - 1] && picture[row][numberOfCols - 1] == '1')
        {
            VisitIsland(row, numberOfCols - 1, isVisited, picture, numberOfRows, numberOfCols);
        }
    }
    for (int col = 1; col < numberOfCols - 1; col++)
    {
        if (!isVisited[0][col] && picture[0][col] == '1')
        {
            VisitIsland(0, col, isVisited, picture, numberOfRows, numberOfCols);
        }
        if (!isVisited[numberOfRows - 1][col] && picture[numberOfRows - 1][col] == '1')
        {
            VisitIsland(numberOfRows - 1, col, isVisited, picture, numberOfRows, numberOfCols);
        }
    }
}

int CountIslands(char picture[][MaxNumberOfCols], int numberOfRows, int numberOfCols)
{
    bool isVisited[MaxNumberOfRows][MaxNumberOfCols];
    FillTwoDimensionalArrayWithFalse(isVisited, numberOfRows, numberOfCols);

    VisitOuterIsland(isVisited, picture, numberOfRows, numberOfCols);

    int numberOfIslands = 0;
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int col = 0; col < numberOfCols; col++)
        {
            if (!isVisited[row][col] && picture[row][col] == '1')
            {
                VisitIsland(row, col, isVisited, picture, numberOfRows, numberOfCols);
                numberOfIslands++;
            }
        }
    }

    return numberOfIslands;
}

int main()
{
    int numberOfRows, numberOfCols;
    scanf("%d%d", &numberOfRows, &numberOfCols);

    char picture[MaxNumberOfRows][MaxNumberOfCols];
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int col = 0; col < numberOfCols; col++)
        {
            scanf(" %c", &picture[row][col]);
        }
    }

    int numberOfIslands = CountIslands(picture, numberOfRows, numberOfCols);
    printf("%d\n", numberOfIslands);
    return 0;
}