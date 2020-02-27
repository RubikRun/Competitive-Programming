//checked - 100%

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define MaxNumberOfVertices 100
#define MaxPesho 10

char letters[MaxNumberOfVertices];
char pesho[MaxPesho];
int peshoLen;

int numberOfVertices;
vector<int> neighbours[MaxNumberOfVertices];

int numberOfPaths;
int table[MaxPesho][MaxNumberOfVertices];

void Input()
{
    scanf("%d", &numberOfVertices);

    int numberOfEdges;
    scanf("%d", &numberOfEdges);

    scanf("%s", letters);

    int a, b;
    for (int i = 0; i < numberOfEdges; i++)
    {
        scanf("%d %d", &a, &b);
        a--;
        b--;

        neighbours[a].push_back(b);
        if (a != b)
        {
            neighbours[b].push_back(a);
        }
    }

    scanf("%s", pesho);
    peshoLen = (int)strlen(pesho);
}

void InitTable()
{
    for (int i = 0; i < peshoLen; i++)
    {
        for (int j = 0; j < numberOfVertices; j++)
        {
            table[i][j] = -1;
        }
    }
}

int CountPaths(int peshoIndex, int prevVertex)
{
    if (peshoIndex >= peshoLen)
    {
        return 1;
    }
    if (table[peshoIndex][prevVertex] != -1)
    {
        return table[peshoIndex][prevVertex];
    }

    int numberOfPaths = 0;

    for (int i = 0; i < neighbours[prevVertex].size(); i++)
    {
        int currentNeighbour = neighbours[prevVertex][i];

        if (letters[currentNeighbour] == pesho[peshoIndex])
        {
            numberOfPaths += CountPaths(peshoIndex + 1, currentNeighbour);
        }
    }

    table[peshoIndex][prevVertex] = numberOfPaths;
    return numberOfPaths;
}

void Solve()
{
    numberOfPaths = 0;

    InitTable();
    for (int i = 0; i < numberOfVertices; i++)
    {
        if (letters[i] == pesho[0])
        {
            numberOfPaths += CountPaths(1, i);
        }
    }

    printf("%d\n", numberOfPaths);
}

int main()
{
    Input();
    Solve();
}