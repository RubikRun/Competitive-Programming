#include <iostream>
using namespace std;

#define MAXN 12
#define MAXM 12

int n, m;
char matrix[MAXN][MAXM];

int sRow, sCol;
int jumps;

void ReadMatrix()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> matrix[i];
    }
}

void PrintMatrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == sRow && j == sCol)
            {
                cout << 'S';
            }
            else
            {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
}

bool ExtractPlayer()
{
    for (int i = 0; i < m; i++)
    {
        if (matrix[n - 1][i] == 'S')
        {
            sRow = n - 1;
            sCol = i;
            matrix[n - 1][i] = '0';
        }
    }
    return false;
}

bool ReadCommand(int& targetRow, int& steps)
{
    return (cin >> targetRow && cin >> steps);
}

bool ExecuteCommand(int targetRow, int steps)
{
    char newRow[MAXM];
    for (int i = 0; i < m; i++)
    {
        newRow[(i + steps) % m] = matrix[targetRow][i];
    }
    for (int i = 0; i < m; i++)
    {
        matrix[targetRow][i] = newRow[i];
    }

    if (matrix[sRow - 1][sCol] == '-')
    {
        sRow--;
        jumps++;
    }
    //judging by examples this should be here
    //jumps++;
}

int main()
{
    ReadMatrix();
    ExtractPlayer();
    jumps = 0;

    int notSpecifiedInProblemDescriptionButOkay;
    cin >> notSpecifiedInProblemDescriptionButOkay;

    int targetRow, steps;
    while (ReadCommand(targetRow, steps))
    {
        ExecuteCommand(targetRow, steps);
    }

    if (sRow == 0)
    {
        cout << "Win" << endl;
    }
    else
    {
        //Also not sepcified in problem description
        cout << "Lose" << endl;
    }
    cout << "Total Jumps: " << jumps << endl;
    PrintMatrix();
}