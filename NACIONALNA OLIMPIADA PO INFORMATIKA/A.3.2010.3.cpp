//checked - 90%

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
#define MaxNumberOfRows 100
#define MaxNumberOfCols 100
#define MaxNumberOfParticles 200

int numberOfRows, numberOfCols;
int period, speed, energy;

int numberOfParticles;

int tableA[MaxNumberOfRows][MaxNumberOfCols];
int tableB[MaxNumberOfRows][MaxNumberOfCols];

int graph[MaxNumberOfParticles][MaxNumberOfParticles][2];
vector<int> path;

bool hasFlowA[MaxNumberOfParticles];
bool hasFlowB[MaxNumberOfParticles];

bool usedA[MaxNumberOfParticles];
bool usedB[MaxNumberOfParticles];

bool debugMode = false;

void Input()
{
    scanf("%d %d", &numberOfCols, &numberOfRows);
    scanf("%d %d", &period, &speed);
    energy = period * speed;

    numberOfParticles = 0;
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            scanf("%d", &tableA[i][j]);
            numberOfParticles += tableA[i][j];
        }
    }
    int numberOfParticlesB = 0;
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            scanf("%d", &tableB[i][j]);
            numberOfParticlesB += tableB[i][j];
        }
    }

    if (numberOfParticles != numberOfParticlesB)
    {
        numberOfParticles = -1;
    }
}

bool CanReach(int r1, int c1, int r2, int c2)
{
    int dist = abs(r1 - r2) + abs(c1 - c2);
    if (dist > energy) return false;
    return ((energy - dist) % 2 == 0);
}

void ConstructGraph()
{
    for (int i = 0; i < numberOfParticles; i++)
    {
        for (int j = 0; j < numberOfParticles; j++)
        {
            graph[i][j][0] = 0;
            graph[i][j][1] = 0;
        }
    }

    int aIndex = 0, bIndex;
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            if (tableA[i][j] > 0)
            {
                bIndex = 0;
                for (int r = 0; r < numberOfRows; r++)
                {
                    for (int c = 0; c < numberOfCols; c++)
                    {
                        if (tableB[r][c] > 0)
                        {
                            if (CanReach(i, j, r, c))
                            {
                                for (int f = aIndex; f < aIndex + tableA[i][j]; f++)
                                {
                                    for (int g = bIndex; g < bIndex + tableB[r][c]; g++)
                                    {
                                        graph[f][g][0] = 1;
                                    }
                                }
                            }
                            bIndex += tableB[r][c];
                        }

                    }
                }
                aIndex += tableA[i][j];
            }
        }
    }
}

bool FindPath(int root)
{
    path.push_back(root);
    usedA[root] = true;

    for (int i = 0; i < numberOfParticles; i++)
    {
        if (!usedB[i] && graph[root][i][0] && !hasFlowB[i])
        {
            path.push_back(i);
            return true;
        }
    }

    for (int i = 0; i < numberOfParticles; i++)
    {
        if (!usedB[i] && graph[root][i][0])
        {
            for (int j = 0; j < numberOfParticles; j++)
            {
                if (!usedA[j] && graph[i][j][1])
                {
                    path.push_back(i);
                    usedB[i] = true;
                    if (FindPath(j))
                    {
                        return true;
                    }
                }
            }
        }
    }

    path.pop_back();
    usedA[root] = false;

    return false;
}

int GetMaxFlow()
{
    for (int i = 0; i < numberOfParticles; i++)
    {
        hasFlowA[i] = false;
        hasFlowB[i] = false;
        usedA[i] = false;
        usedA[i] = false;
    }

    int flow = 0;

    while (flow < 10)
    {
        int oldFlow = flow;

        for (int i = 0; i < numberOfParticles; i++)
        {
            if (!hasFlowA[i])
            {
                if (FindPath(i))
                {
                    if (debugMode)
                    {
                        for (int k = 0; k < numberOfParticles; k++)
                        {
                            for (int l = 0; l < numberOfParticles; l++)
                            {
                                printf("Edge (%d, %d) directions: %d %d\n", k, l, graph[k][l][0], graph[k][l][1]);
                            }
                        }
                    }
                    if (debugMode)
                    {
                        printf("Path found: ");
                        for (int k = 0; k < path.size(); k++)
                        {
                            printf("%d ", path[k]);
                        }
                        printf("\n");
                    }
                    for (int j = 0; j < path.size() - 1; j++)
                    {
                        if (j % 2 == 0)
                        {
                            graph[path[j]][path[j + 1]][0] = 0;
                            graph[path[j]][path[j + 1]][1] = 1;
                            usedA[j] = false;
                        }
                        else
                        {
                            graph[path[j + 1]][path[j]][0] = 1;
                            graph[path[j + 1]][path[j]][1] = 0;
                            usedB[j] = false;
                        }
                    }
                    hasFlowA[path[0]] = true;
                    hasFlowB[path.back()] = true;
                    usedB[path.back()] = false;
                    path.clear();
                    flow++;
                }
            }
        }

        if (flow == oldFlow) break;
    }

    return flow;
}

int main()
{
    Input();

    if (numberOfParticles == -1)
    {
        printf("N\n");
        return 0;
    }

    ConstructGraph();

    if (debugMode)
    {
        printf("Number of particles: %d\n", numberOfParticles);
        for (int i = 0; i < numberOfParticles; i++)
        {
            printf("Particle %d can reach: ", i);
            for (int j = 0; j < numberOfParticles; j++)
            {
                if (graph[i][j][0] == 1)
                {
                    printf("%d ", j);
                }
            }
            printf("\n");
        }
    }

    int maxFlow = GetMaxFlow();
    if (debugMode) printf("\nMax flow found to be %d\n", maxFlow);

    if (maxFlow == numberOfParticles)
    {
        printf("Y\n");
    }
    else
    {
        printf("N\n");
    }

    return 0;
}
