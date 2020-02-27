#include <iostream>

using namespace std;
#define MaxHeight 100
#define MaxWidth 100

char matrix[MaxHeight + 1][MaxWidth + 1];
int height, width;

void ReadMatrix()
{
    cin >> height >> width;

    for (int i = 0; i < height; i++)
    {
        cin >> matrix[i];
    }
}

void PrintMatrix()
{
    for (int i = 0; i < height; i++)
    {
        cout << matrix[i] << endl;
    }
}

bool IsValidPoint(int row, int col) { return (row >= 0 && row < height && col >= 0 && col < width); }

void TransformMatrix()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (matrix[i][j] == '*')
            {
                continue;
            }

            int mines = 0;

            if (IsValidPoint(i - 1, j - 1) && matrix[i - 1][j - 1] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i - 1, j) && matrix[i - 1][j] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i - 1, j + 1) && matrix[i - 1][j + 1] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i, j - 1) && matrix[i][j - 1] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i, j + 1) && matrix[i][j + 1] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i + 1, j - 1) && matrix[i + 1][j - 1] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i + 1, j) && matrix[i + 1][j] == '*')
            {
                mines++;
            }
            if (IsValidPoint(i + 1, j + 1) && matrix[i + 1][j + 1] == '*')
            {
                mines++;
            }

            matrix[i][j] = mines + '0';
        }
    }
}

int main()
{
    for (int i = 1; true; i++)
    {
        ReadMatrix();
        if (height == 0)
        {
            break;
        }
        if (i > 1)
        {
            cout << endl;
        }
        TransformMatrix();

        cout << "Field #" << i << ":" << endl;
        PrintMatrix();
    }

    return 0;
}
