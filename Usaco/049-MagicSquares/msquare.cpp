/*
ID: borisd22
TASK: msquare
LANG: C++
*/

#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;
#define Read fin
#define Write fout

ifstream fin ("msquare.in");
ofstream fout ("msquare.out");

struct Node
{
    int dist;
    char action;
    vector<int> prev;
};

void ApplyA(vector<int>& x)
{
    reverse(x.begin(), x.end());
}

void ApplyB(vector<int>& x)
{
    int three = x[3];
    x[3] = x[2];
    x[2] = x[1];
    x[1] = x[0];
    x[0] = three;

    int four = x[4];
    x[4] = x[5];
    x[5] = x[6];
    x[6] = x[7];
    x[7] = four;
}

void ApplyC(vector<int>& x)
{
     int one = x[1];
     x[1] = x[6];
     x[6] = x[5];
     x[5] = x[2];
     x[2] = one;
}

void CopyVector(vector<int>& a, vector<int>& b)
{
    b.clear();

    for (int i = 0; i < a.size(); i++)
    {
        b.push_back(a[i]);
    }
}

bool VectorsAreEqual(vector<int>& a, vector<int>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}

vector<char> FindPath(vector<int> destination)
{
    vector<int> initial = {1, 2, 3, 4, 5, 6, 7, 8};

    if (VectorsAreEqual(initial, destination))
    {
        return {};
    }

    map< vector<int>, Node > distActionPrev;
    distActionPrev[initial] = {0, '0', {}};

    queue< vector<int> > q;
    q.push(initial);
    while (!q.empty())
    {
        vector<int> a = q.front();
        q.pop();

        vector<int> b;
        CopyVector(a, b);
        ApplyA(b);
        if (distActionPrev.find(b) == distActionPrev.end())
        {
            distActionPrev[b] = {distActionPrev[a].dist + 1, 'A', a};
            if (VectorsAreEqual(b, destination))
            {
                break;
            }
            q.push(b);
        }

        CopyVector(a, b);
        ApplyB(b);
        if (distActionPrev.find(b) == distActionPrev.end())
        {
            distActionPrev[b] = {distActionPrev[a].dist + 1, 'B', a};
            if (VectorsAreEqual(b, destination))
            {
                break;
            }
            q.push(b);
        }

        CopyVector(a, b);
        ApplyC(b);
        if (distActionPrev.find(b) == distActionPrev.end())
        {
            distActionPrev[b] = {distActionPrev[a].dist + 1, 'C', a};
            if (VectorsAreEqual(b, destination))
            {
                break;
            }
            q.push(b);
        }
    }

    vector<char> path;
    while (distActionPrev[destination].dist > 0)
    {
        path.push_back(distActionPrev[destination].action);
        destination = distActionPrev[destination].prev;
    }
    reverse(path.begin(), path.end());

    return path;
}

int main()
{
    vector<int> destination;
    for (int i = 0; i < 8; i++)
    {
        destination.push_back(0);
        Read >> destination.back();
    }

    vector<char> path = FindPath(destination);

    Write << path.size() << endl;
    for (int i = 0; i < path.size(); i++)
    {
        Write << path[i];
    }
    Write << endl;

    return 0;
}
