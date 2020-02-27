//checked - 100%

#include <cstdio>
using namespace std;

int sudoku[9][9];

bool FindByRow(int row, int col)
{
    bool canBe[10]; for (int i = 1; i <= 9; i++) canBe[i] = true;

    for (int i = 0; i < 9; i++)
    {
        canBe[sudoku[row][i]] = false;
    }

    int shouldBe = -1;
    for (int i = 1; i <= 9; i++)
    {
        if (canBe[i])
        {
            if (shouldBe == -1)
            {
                shouldBe = i;
            }
            else
            {
                return false;
            }
        }
    }

    if (shouldBe == -1)
    {
        return false;
    }

    sudoku[row][col] = shouldBe;

    return true;
}

bool FindByCol(int row, int col)
{
    bool canBe[10]; for (int i = 1; i <= 9; i++) canBe[i] = true;

    for (int i = 0; i < 9; i++)
    {
        canBe[sudoku[i][col]] = false;
    }

    int shouldBe = -1;
    for (int i = 1; i <= 9; i++)
    {
        if (canBe[i])
        {
            if (shouldBe == -1)
            {
                shouldBe = i;
            }
            else
            {
                return false;
            }
        }
    }

    if (shouldBe == -1)
    {
        return false;
    }

    sudoku[row][col] = shouldBe;

    return true;
}

bool FindBySquare(int row, int col)
{
    int cornerRow = row / 3 * 3;
    int cornerCol = col / 3 * 3;

    bool canBe[10]; for (int i = 1; i <= 9; i++) canBe[i] = true;

    for (int i = cornerRow; i < cornerRow + 3; i++)
    {
        for (int j = cornerCol; j < cornerCol + 3; j++)
        {
            canBe[sudoku[i][j]] = false;
        }
    }

    int shouldBe = -1;
    for (int i = 1; i <= 9; i++)
    {
        if (canBe[i])
        {
            if (shouldBe == -1)
            {
                shouldBe = i;
            }
            else
            {
                return false;
            }
        }
    }

    if (shouldBe == -1)
    {
        return false;
    }

    sudoku[row][col] = shouldBe;

    return true;
}

void FindTile(int row, int col)
{
    if (FindByRow(row, col))
    {
        return;
    }
    if (FindByCol(row, col))
    {
        return;
    }
    FindBySquare(row, col);
}

void MakeMove()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku[row][col] == 0)
            {
                FindTile(row, col);
            }
        }
    }
}

bool SudokuIsDone()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku[row][col] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void ReadSudoku()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            scanf("%d", &sudoku[row][col]);
        }
    }
}

void PrintSudoku()
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            printf("%d ", sudoku[row][col]);
        }
        printf("%d", sudoku[row][8]);
        if (row < 8)
        {
            printf("\n");
        }

    }
}

int main()
{
    ReadSudoku();

    while (!SudokuIsDone())
    {
        MakeMove();
    }

    PrintSudoku();

    return 0;
}

/*
5 3 4 6 7 8 9 1 2
6 0 2 0 9 5 3 4 8
1 9 8 3 4 2 5 6 7
8 5 9 7 6 1 4 2 3
4 2 6 8 5 3 7 9 1
7 1 3 9 2 4 8 5 6
9 6 1 5 3 7 2 8 4
2 0 7 0 1 9 6 3 5
3 4 5 2 8 6 1 7 9
 */