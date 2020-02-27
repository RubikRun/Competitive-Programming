//checked - 100%

#include <cstdio>

using namespace std;

#define MAXN 6

int table[MAXN * MAXN][MAXN * MAXN];
char symbols[MAXN * MAXN];
int n;

void FillTable()
{
    for (int row = 0; row < n * n; row++)
    {
        table[row][0] = row % n * n + row / n;
        for (int col = 1; col < n * n; col++)
        {
            table[row][col] = (table[row][col - 1] + 1) % (n * n);
        }
    }
}

void PrintTableWithSymbols()
{
    for (int row = 0; row < n * n; row++)
    {
        for (int col = 0; col < n * n; col++)
        {
            printf("%c", symbols[table[row][col]]);
        }
        printf("\n");
    }
}

int main()
{
    scanf("%d", &n);
    FillTable();

    char currentLine[MAXN + 1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", currentLine);
        for (int j = 0; j < n; j++)
        {
            symbols[i * n + j] = currentLine[j];
        }
    }

    PrintTableWithSymbols();

    return 0;
}