/*
ID: borisd22
TASK: camelot
LANG: C++
*/

//Slow but I don't care

#include <fstream>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfRows 30
#define MaxNumberOfCols 26
#define MaxNumberOfKnights 780
#define Infinity 10000

ifstream fin ("camelot.in");
ofstream fout ("camelot.out");

int knightDeltas[8][2] = { {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1} };

int numberOfRows, numberOfCols;

pair<int, int> king;
vector< pair<int, int> > knights;

int knightDist[MaxNumberOfRows][MaxNumberOfCols][MaxNumberOfRows][MaxNumberOfCols];

bool ReadPosition(int& row, int& col)
{
    char colChar;
    if (Read >> colChar >> row)
    {
        row--;
        col = colChar - 'A';
        return true;
    }
    return false;
}

void Input()
{
    Read >> numberOfRows >> numberOfCols;
    ReadPosition(king.first, king.second);

    int knightRow, knightCol;
    while (ReadPosition(knightRow, knightCol))
    {
        knights.push_back({knightRow, knightCol});
    }
}

bool InBoard(pair<int, int> x) { return (x.first >= 0 && x.second >= 0 && x.first < numberOfRows && x.second < numberOfCols); }

vector< pair<int, int> > GetKnightAdj(pair<int, int> knight)
{
    vector< pair<int, int> > adj;
    for (int i = 0; i < 8; i++)
    {
        pair<int, int> x = {knight.first + knightDeltas[i][0], knight.second + knightDeltas[i][1]};
        if (InBoard(x))
        {
            adj.push_back(x);
        }
    }
    return adj;
}

void KnightBFS(pair<int, int> x)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            knightDist[x.first][x.second][i][j] = Infinity;
        }
    }
    knightDist[x.first][x.second][x.first][x.second] = 0;

    queue< pair<int, int> > q;
    q.push(x);
    while (!q.empty())
    {
        pair<int, int> a = q.front();
        q.pop();

        vector< pair<int, int> > adj = GetKnightAdj(a);
        for (int i = 0; i < adj.size(); i++)
        {
            pair<int, int> b = adj[i];
            if (knightDist[x.first][x.second][b.first][b.second] == Infinity)
            {
                knightDist[x.first][x.second][b.first][b.second] = knightDist[x.first][x.second][a.first][a.second] + 1;
                q.push(b);
            }
        }
    }
}

void FillKnightDist()
{
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            KnightBFS({i, j});
        }
    }
}

int GetMovesToRoot(pair<int, int> root)
{
    int knightSum = 0;
    for (int i = 0; i < knights.size(); i++)
    {
        knightSum += knightDist[knights[i].first][knights[i].second][root.first][root.second];
    }

    int moves = knightSum + abs(king.first - root.first) + abs(king.second - root.second);

    for (int k = 0; k < knights.size(); k++)
    {
        for (int i = 0; i < numberOfRows; i++)
        {
            for (int j = 0; j < numberOfCols; j++)
            {
                moves = min(moves, knightSum - knightDist[knights[k].first][knights[k].second][root.first][root.second] +
                    knightDist[knights[k].first][knights[k].second][i][j] + abs(king.first - i) + abs(king.second - j) + knightDist[i][j][root.first][root.second]);
            }
        }
    }

    return moves;
}

int GetMinMoves()
{
    int minMoves = Infinity;

    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            minMoves = min(minMoves, GetMovesToRoot({i, j}));
        }
    }

    return minMoves;
}

int main()
{
    Input();
    FillKnightDist();

    int minMoves = GetMinMoves();
    Write << minMoves << endl;

    return 0;
}
