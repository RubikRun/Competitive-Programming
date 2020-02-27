//checked - 90%

#include <cstdio>
#include <vector>

using namespace std;
#define MaxSize 20
#define MaxNumberOfVertices 3 * MaxSize * MaxSize - 3 * MaxSize + 1

int size;

vector<int> adj[MaxNumberOfVertices + 1];
int numberOfVertices;

int first, last;
long long unsigned numberOfPaths[MaxNumberOfVertices + 1][MaxNumberOfVertices + 1];

void Input()
{
    scanf("%d %d %d", &size, &first, &last);
    numberOfVertices = 3 * size * size - 3 * size + 1;
}

void ConstructGraph()
{
    int matrix[MaxSize * 2][MaxSize * 2];

    int x = 1;
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size + i - 1; j++)
        {
            matrix[i][j] = x++;
        }
    }
    for (int i = size + 1; i <= size * 2 - 1; i++)
    {
        for (int j = 1; j <= 3 * size - i - 1; j++)
        {
            matrix[i][j] = x++;
        }
    }

    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size + i - 1; j++)
        {
            if (j < size + i - 1) adj[matrix[i][j]].push_back(matrix[i][j + 1]);
            if (i < size) adj[matrix[i][j]].push_back(matrix[i + 1][j]);
            if (i == size && j > 1) adj[matrix[i][j]].push_back(matrix[i + 1][j - 1]);
            if (i < size) adj[matrix[i][j]].push_back(matrix[i + 1][j + 1]);
            if (i == size && j < size + i - 1) adj[matrix[i][j]].push_back(matrix[i + 1][j]);
        }
    }
    for (int i = size + 1; i <= size * 2 - 1; i++)
    {
        for (int j = 1; j <= 3 * size - i - 1; j++)
        {
            if (j < 3 * size - i - 1) adj[matrix[i][j]].push_back(matrix[i][j + 1]);
            if (i < size * 2 - 1)
            {
                if (j > 1) adj[matrix[i][j]].push_back(matrix[i + 1][j - 1]);
                if (j < 3 * size - i - 1) adj[matrix[i][j]].push_back(matrix[i + 1][j]);
            }
        }
    }
}

void FillNumberOfPaths()
{
    for (int i = 1; i <= numberOfVertices; i++)
    {
        numberOfPaths[i][0] = 0;
    }
    numberOfPaths[last][0] = 1;

    for (int pathLen = 1; pathLen <= numberOfVertices; pathLen++)
    {
        for (int i = 1; i <= numberOfVertices; i++)
        {
            numberOfPaths[i][pathLen] = 0;
            for (int k = 0; k < adj[i].size(); k++)
            {
                int child = adj[i][k];
                numberOfPaths[i][pathLen] += numberOfPaths[child][pathLen - 1];
            }
        }
    }
}

int main()
{
    Input();
    if (first >= last)
    {
        printf("0 0\n");
        return 0;
    }
    ConstructGraph();
    FillNumberOfPaths();

    for (int pathLen = numberOfVertices; pathLen >= 0; pathLen--)
    {
        if (numberOfPaths[first][pathLen] != 0)
        {
            printf("%d %llu\n", pathLen + 1, numberOfPaths[first][pathLen]);
            return 0;
        }
    }

    printf("0 0\n");
    return 0;
}
