/*
ID: borisd22
TASK: teamwork
LANG: C++
*/

#include <fstream>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfCows 5000
#define Infinity 2147483647

ifstream fin ("teamwork.in");
ofstream fout ("teamwork.out");

int skills[MaxNumberOfCows];
int numberOfCows;

int teamSizeLimit;

int maxSum[MaxNumberOfCows][MaxNumberOfCows];

void Input()
{
    Read >> numberOfCows >> teamSizeLimit;

    for (int i = 0; i < numberOfCows; i++)
    {
        Read >> skills[i];
    }
}

void InitMaxSum()
{
    for (int i = 0; i < numberOfCows; i++)
    {
        for (int j = 0; j < numberOfCows; j++)
        {
            maxSum[i][j] = -1;
        }
    }
}

int GetMaxSum(int a, int b)
{
    if (a > b)
    {
        maxSum[a][b] = 0;
        return maxSum[a][b];
    }

    if (maxSum[a][b] != -1)
    {
        return maxSum[a][b];
    }

    int bestSkill = -1;
    for (int i = a; i <= b; i++)
    {
        bestSkill = max(bestSkill, skills[i]);
    }

    if (b - a + 1 <= teamSizeLimit)
    {
        maxSum[a][b] = bestSkill * (b - a + 1);
        return maxSum[a][b];
    }

    for (int i = a; i + teamSizeLimit - 1 <= b; i++)
    {
        bool hasLeader = false;
        for (int j = i; j < i + teamSizeLimit; j++)
        {
            if (skills[j] == bestSkill)
            {
                hasLeader = true;
                break;
            }
        }
        if (!hasLeader) continue;

        maxSum[a][b] = max(maxSum[a][b], GetMaxSum(a, i - 1) + bestSkill * teamSizeLimit + GetMaxSum(i + teamSizeLimit, b));
    }

    return maxSum[a][b];
}

int main()
{
    Input();

    InitMaxSum();
    Write << GetMaxSum(0, numberOfCows - 1) << endl;

    return 0;
}
