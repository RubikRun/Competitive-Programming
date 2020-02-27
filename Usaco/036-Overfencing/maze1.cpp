/*
ID: borisd22
TASK: maze1
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

ifstream fin ("maze1.in");
ofstream fout ("maze1.out");

#define MaxWidth 38
#define MaxHeight 100

int width;
int height;

char maze[MaxHeight * 2 + 2][MaxWidth * 2 + 2];

void Input()
{
    fin >> width >> height;
    fin.getline(maze[0], 0); //C++ specific

    for (int i = 0; i < height * 2 + 1; i++)
    {
        fin.getline(maze[i], MaxWidth * 2 + 2);
    }
}

#define MaxNumberOfVertices 3800

vector<int> exits;

struct Graph
{
    int numberOfVertices;
    vector<int> adj[MaxNumberOfVertices];
};

Graph graph;

void ConstructGraph()
{
    graph.numberOfVertices = width * height;

    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        for (int j = i; j < graph.numberOfVertices; j++)
        {
            #define AreAdj graph.adj[i].push_back(j); graph.adj[j].push_back(i); continue;

            if (i == j)
            {
                continue;
            }

            int iRow = i / width, iCol = i % width;
            int jRow = j / width, jCol = j % width;

            if (jRow - iRow == 1 && jCol - iCol == 0)
            {
                if (maze[jRow * 2][iCol * 2 + 1] == ' ')
                {
                    AreAdj
                }
                else
                {
                    continue;
                }
            }
            else if (jRow - iRow == 0 && jCol - iCol == 1)
            {
                if (maze[iRow * 2 + 1][jCol * 2] == ' ')
                {
                    AreAdj
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void FindExits()
{
    for (int col = 0; col < width; col++)
    {
        if (maze[0][col * 2 + 1] == ' ')
        {
            exits.push_back(col);
        }
        if (maze[height * 2][col * 2 + 1] == ' ')
        {
            exits.push_back((height - 1) * width + col);
        }
    }

    for (int row = 0; row < height; row++)
    {
        if (maze[row * 2 + 1][0] == ' ')
        {
            exits.push_back(row * width);
        }
        if (maze[row * 2 + 1][width * 2] == ' ')
        {
            exits.push_back((row + 1) * width - 1);
        }
    }
}

void FillDist(int root, int dist[])
{
    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        dist[i] = -1;
    }
    dist[root] = 0;

    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int currVertex = q.front();
        q.pop();

        for (int i = 0; i < graph.adj[currVertex].size(); i++)
        {
            int nextVertex = graph.adj[currVertex][i];
            if (dist[nextVertex] != -1)
            {
                continue;
            }

            dist[nextVertex] = dist[currVertex] + 1;
            q.push(nextVertex);
        }
    }
}

int GetMaxDist()
{
    int maxDist = 0;

    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        int dist[MaxNumberOfVertices];
        FillDist(i, dist);

        int distToExit1 = dist[exits[0]];
        int distToExit2 = dist[exits[1]];

        maxDist = max(maxDist, min(distToExit1, distToExit2));
    }

    return maxDist;
}

int main()
{
    Input();
    ConstructGraph();
    FindExits();

    fout << GetMaxDist() + 1 << endl;

    return 0;
}