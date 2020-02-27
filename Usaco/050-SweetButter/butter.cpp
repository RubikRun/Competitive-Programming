/*
ID: borisd22
TASK: butter
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfCows 500
#define MaxNumberOfPastures 800
#define Infinity 1000000

ifstream fin ("butter.in");
ofstream fout ("butter.out");

int numberOfCows;
int numberOfPastures;

int cowPasture[MaxNumberOfCows];
int adjMatrix[MaxNumberOfPastures][MaxNumberOfPastures];
int distMatrix[MaxNumberOfPastures][MaxNumberOfPastures];

vector<int> adjList[MaxNumberOfPastures];

void Input()
{
    int numberOfPaths;
    Read >> numberOfCows >> numberOfPastures >> numberOfPaths;

    for (int i = 0; i < numberOfCows; i++)
    {
        Read >> cowPasture[i];
        cowPasture[i]--;
    }

    for (int i = 0; i < numberOfPastures; i++)
    {
        for (int j = 0; j < numberOfPastures; j++)
        {
            adjMatrix[i][j] = -1;
        }
    }
    int a, b, w;
    for (int i = 0; i < numberOfPaths; i++)
    {
        Read >> a >> b >> w;
        a--;
        b--;

        adjMatrix[a][b] = w;
        adjMatrix[b][a] = w;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
}

void SPFA(int root)
{
    for (int i = 0; i < numberOfPastures; i++)
    {
        distMatrix[root][i] = Infinity;
    }
    distMatrix[root][root] = 0;

    bool inQ[MaxNumberOfPastures];
    for (int i = 0; i < numberOfPastures; i++)
    {
        inQ[i] = false;
    }

    queue<int> q;
    q.push(root);
    inQ[root] = true;
    while (!q.empty())
    {
        int a = q.front();
        q.pop();
        inQ[a] = false;

        for (int i = 0; i < adjList[a].size(); i++)
        {
            int b = adjList[a][i];
            if (distMatrix[root][a] + adjMatrix[a][b] < distMatrix[root][b])
            {
                distMatrix[root][b] = distMatrix[root][a] + adjMatrix[a][b];
                if (!inQ[b])
                {
                    q.push(b);
                    inQ[b] = true;
                }
            }
        }
    }

    for (int i = 0; i < numberOfPastures; i++)
    {
        distMatrix[i][root] = distMatrix[root][i];
    }
}

void FillDistMatrix()
{
    for (int i = 0; i < numberOfPastures; i++)
    {
        SPFA(i);
    }
}

int GetCowWalk(int basePasture)
{
    int cowWalk = 0;

    for (int i = 0; i < numberOfCows; i++)
    {
        cowWalk += distMatrix[cowPasture[i]][basePasture];
    }

    return cowWalk;
}

int GetMinCowWalk()
{
    int minCowWalk = Infinity;

    for (int basePasture = 0; basePasture < numberOfPastures; basePasture++)
    {
        minCowWalk = min(minCowWalk, GetCowWalk(basePasture));
    }

    return minCowWalk;
}

void Solve()
{
    FillDistMatrix();

    Write << GetMinCowWalk() << endl;
}

int main()
{
    Input();
    Solve();

    return 0;
}
