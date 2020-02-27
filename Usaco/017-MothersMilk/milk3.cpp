/*
ID: borisd22
TASK: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("milk3.out");
ifstream fin ("milk3.in");

#define MaxCapacity 20
#define Reach if (!stateCanBeReached[newA][newB][newC]){stateCanBeReached[newA][newB][newC] = true; ReachAllStates(newA, newB, newC);}

bool stateCanBeReached[MaxCapacity + 1][MaxCapacity + 1][MaxCapacity + 1];

int A, B, C;

void Init()
{
    for (int i = 0; i <= A; i++)
    {
        for (int j = 0; j <= B; j++)
        {
            for (int k = 0; k <= C; k++)
            {
                stateCanBeReached[i][j][k] = false;
            }
        }
    }
    stateCanBeReached[0][0][C] = true;
}

void ReachAllStates(int a, int b, int c)
{
    int newA = a, newB = b, newC = c;

    newA = max(a + b - B, 0);
    newB = min(B, b + a);
    Reach

    newB = max(b + a - A, 0);
    newA = min(A, a + b);
    Reach

    newB = b;


    newA = max(a + c - C, 0);
    newC = min(C, c + a);
    Reach

    newC = max(c + a - A, 0);
    newA = min(A, a + c);
    Reach

    newA = a;

    newB = max(b + c - C, 0);
    newC = min(C, c + b);
    Reach

    newC = max(c + b - B, 0);
    newB = min(B, b + c);
    Reach
}

vector<int> GetZeroStatesCs()
{
    vector<int> result;

    for (int j = 0; j <= C; j++)
    {
        for (int i = 0; i <= B; i++)
        {
            if (stateCanBeReached[0][i][j])
            {
                result.push_back(j);
            }
        }
    }

    return result;
}

int main()
{
    fin >> A >> B >> C;
    Init();
    ReachAllStates(0, 0, C);
    vector<int> result = GetZeroStatesCs();

    for (int i = 0; i < result.size() - 1; i++)
    {
        fout << result[i] << " ";
    }
    fout << result.back() << endl;

    return 0;
}

