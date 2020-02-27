#include <iostream>
#include <cstring>
using namespace std;

#define MAXMATRIXSIZE 52
#define MAXCOMMANDLEN 20

const char EndingCommand[MAXCOMMANDLEN] = "eastern";
const int RestsLimit = 10000;

int matrix[MAXMATRIXSIZE][MAXMATRIXSIZE];
int matrixSize;

struct Cell
{
    int row, col;
    bool operator==(const Cell& x)
    {
        return row == x.row && col == x.col;
    }
};

struct Direction
{
    int deltaRow, deltaCol;
};

struct Voyage
{
    Cell start, finish;
    Direction dir;
    int stamina;
};

int AbsVal(int x)
{
    if (x < 0) return (-x);
    return x;
}

void InitMatrix()
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void PrintMatrix()
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int IntParse(char* str)
{
    int result = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        result = result * 10 + (str[i] - '0');
    }

    return result;
}

bool ReadCommand(Voyage& voyage)
{
    char input[MAXCOMMANDLEN];

    cin >> input;
    if (strcmp(input, EndingCommand) == 0)
    {
        cin >> input;
        return false;
    }
    voyage.finish.row = IntParse(input);

    cin >> input;
    voyage.finish.col = IntParse(input);

    cin >> input;
    if (strcmp(input, "left") == 0)
    {
        voyage.dir.deltaRow = 0;
        voyage.dir.deltaCol = -1;
    }
    else if (strcmp(input, "right") == 0)
    {
        voyage.dir.deltaRow = 0;
        voyage.dir.deltaCol = 1;
    }
    else if (strcmp(input, "up") == 0)
    {
        voyage.dir.deltaRow = -1;
        voyage.dir.deltaCol = 0;
    }
    else
    {
        voyage.dir.deltaRow = 1;
        voyage.dir.deltaCol = 0;
    }

    cin >> input;
    voyage.stamina = IntParse(input);

    return true;
}

Cell CellAfterStamina(Cell startCell, Direction dir, int stamina)
{
    return {startCell.row + stamina * dir.deltaRow, startCell.col + stamina * dir.deltaCol};
}

bool IsInsideMatrix(Cell cell)
{
    return !(cell.row < 0 || cell.row >= matrixSize || cell.col < 0 || cell.col >= matrixSize);
}

bool FindNextDir(Direction& nextDir, Direction& currDir, Cell& currCell, Voyage& voyage)
{
    if (currDir.deltaRow == 0)
    {
        if (AbsVal(voyage.finish.row - currCell.row) < voyage.stamina)
        {
            nextDir = {-currDir.deltaCol, 0};
        }
        else
        {
            if (voyage.finish.row < currCell.row)
            {
                nextDir = {-1, 0};
            }
            else
            {
                nextDir = {1, 0};
            }
        }

        if (!IsInsideMatrix(CellAfterStamina(currCell, nextDir, voyage.stamina)))
        {
            nextDir.deltaRow *= (-1);
            if (!IsInsideMatrix(CellAfterStamina(currCell, nextDir, voyage.stamina)))
            {
                return false;
            }
        }
    }
    else
    {
        if (AbsVal(voyage.finish.col - currCell.col) < voyage.stamina)
        {
            nextDir = {0, currDir.deltaRow};
        }
        else
        {
            if (voyage.finish.col < currCell.col)
            {
                nextDir = {0, -1};
            }
            else
            {
                nextDir = {0, 1};
            }
        }

        if (!IsInsideMatrix(CellAfterStamina(currCell, nextDir, voyage.stamina)))
        {
            nextDir.deltaCol *= (-1);
            if (!IsInsideMatrix(CellAfterStamina(currCell, nextDir, voyage.stamina)))
            {
                return false;
            }
        }
    }
    return true;
}

int DoVoyage(Voyage voyage)
{
    if ((voyage.start.row - voyage.finish.row) % voyage.stamina != 0 && (voyage.start.col - voyage.finish.col) % voyage.stamina != 0)
    {
        return -1;
    }

    int alteredMatrix[MAXMATRIXSIZE][MAXMATRIXSIZE];
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            alteredMatrix[i][j] = matrix[i][j];
        }
    }

    Cell currCell = voyage.start;
    Direction currDir = voyage.dir;

    int rests = 0;
    Cell nextCell = CellAfterStamina(currCell, currDir, voyage.stamina);
    if (!IsInsideMatrix(nextCell))
    {
        return -1;
    }
    while (true)
    {
        while (!(currCell == nextCell))
        {
            currCell.row += currDir.deltaRow;
            currCell.col += currDir.deltaCol;

            alteredMatrix[currCell.row][currCell.col]++;
        }

        if (currCell == voyage.finish)
        {
            for (int i = 0; i < matrixSize; i++)
            {
                for (int j = 0; j < matrixSize; j++)
                {
                    matrix[i][j] = alteredMatrix[i][j];
                }
            }
            return rests;
        }
        rests++;
        if (rests > RestsLimit)
        {
            return -1;
        }

        Direction nextDir;
        if (!FindNextDir(nextDir, currDir, currCell, voyage))
        {
            return -1;
        }
        currDir = nextDir;
        nextCell = CellAfterStamina(currCell, currDir, voyage.stamina);
    }
}

int main()
{
    cin >> matrixSize;
    InitMatrix();

    Voyage voyage;
    cin >> voyage.start.row >> voyage.start.col;

    while (ReadCommand(voyage))
    {
        int rests = DoVoyage(voyage);
        if (rests == -1)
        {
            cout << "Voyage impossible" << endl;
        }
        else
        {
            cout << rests << endl;
            voyage.start = voyage.finish;
        }
    }
    PrintMatrix();

    return 0;
}