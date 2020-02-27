#include <iostream>
#include <cstring>
using namespace std;

#define MAXMATRIXSIZE 51
#define MAXCOMMANDLEN 20

const char EndingCommand[MAXCOMMANDLEN] = "Melolemonmelon";

char matrix[MAXMATRIXSIZE][MAXMATRIXSIZE][MAXMATRIXSIZE];
int matrixSize;

int AbsVal(int x)
{
    if (x < 0) return (-x);
    return x;
}

void inputMatrix()
{
    cin >> matrixSize;
    char uselessChar;
    for (int row = 0; row < matrixSize; row++)
    {
        for (int layer = 0; layer < matrixSize; layer++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                cin >> matrix[layer][row][col];
            }
            if (layer < matrixSize - 1)
            {
                cin >> uselessChar;
            }
        }
    }
}

void printMatrix()
{
    for (int row = 0; row < matrixSize; row++)
    {
        for (int layer = 0; layer < matrixSize; layer++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                cout << matrix[layer][row][col];
                if (layer < matrixSize - 1 || col < matrixSize - 1)
                {
                    cout << " ";
                }
            }
            if (layer < matrixSize - 1)
            {
                cout << "| ";
            }
        }
        cout << endl;
    }
}

void Morph(char& c)
{
    switch(c)
    {
        case 'W': c = 'E'; break;
        case 'E': c = 'F'; break;
        case 'F': c = 'A'; break;
        case 'A': c = 'W'; break;
    }
}

void Harvest(int targetLayer, int targetRow, int targetCol)
{
    matrix[targetLayer][targetRow][targetCol] = '0';
    for (int layer = 0; layer < matrixSize; layer++)
    {
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                if (AbsVal(layer - targetLayer) + AbsVal(row - targetRow) + AbsVal(col - targetCol) != 1)
                {
                    Morph(matrix[layer][row][col]);
                }
            }
        }
    }
}

int NumFromString(char* str)
{
    int result = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        result = result * 10 + (str[i] - '0');
    }

    return result;
}

bool ReadCommand(int& layer, int& row, int& col)
{
    char input[MAXCOMMANDLEN];

    cin >> input;
    if (strcmp(input, EndingCommand) == 0)
    {
        return false;
    }
    layer = NumFromString(input);

    cin >> input;
    row = NumFromString(input);

    cin >> input;
    col = NumFromString(input);

    return true;
}

int main()
{
    inputMatrix();

    int targetLayer, targetRow, targetCol;
    while (ReadCommand(targetLayer, targetRow, targetCol))
    {
        Harvest(targetLayer, targetRow, targetCol);
    }

    printMatrix();

    return 0;
}