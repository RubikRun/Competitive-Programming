//checked - 100%

#include <cstdio>

using namespace std;
#define MaxNumberOfLilies 100000
#define MaxLog 20
#define NumberOfLilyTypes 5

int numberOfLilies;

int juPerLily[MaxNumberOfLilies];
int lilyType[MaxNumberOfLilies];
int distLimit[MaxNumberOfLilies];

int maxJu[MaxNumberOfLilies];

int RMQ[MaxNumberOfLilies][MaxLog][NumberOfLilyTypes + 1];

void Input()
{
    scanf("%d", &numberOfLilies);

    for (int i = 0; i < numberOfLilies; i++)
    {
        scanf("%d %d %d", &juPerLily[i], &lilyType[i], &distLimit[i]);
    }
}

void UpdateRMQ(int ind, int t)
{
    RMQ[ind][0][t] = ind;

    for (int p = 1; ind + (1 << p) - 1 < numberOfLilies; p++)
    {
        int a = RMQ[ind][p - 1][t];
        int b = RMQ[ind + (1 << (p - 1))][p - 1][t];

        if (maxJu[a] + (numberOfLilies - a) * t > maxJu[b] + (numberOfLilies - b) * t)
        {
            RMQ[ind][p][t] = a;
        }
        else
        {
            RMQ[ind][p][t] = b;
        }
    }
}

int QueryRMQ(int a, int b, int t)
{
    if (a < 0) a = 0;
    if (b >= numberOfLilies) b = numberOfLilies - 1;

    int result = -1;
    int p = MaxLog;
    while (a <= b)
    {
        while ((1 << p) > b - a + 1) p--;

        int r = RMQ[a][p][t];
        if (result == -1 || maxJu[r] + (numberOfLilies - r) * t > maxJu[result] + (numberOfLilies - result) * t)
        {
            result = r;
        }
        a += (1 << p);
    }

    return result;
}

void FillMaxJu()
{
    maxJu[numberOfLilies - 1] = juPerLily[numberOfLilies - 1];
    for (int t = 1; t <= NumberOfLilyTypes; t++) RMQ[numberOfLilies - 1][0][t] = numberOfLilies - 1;

    for (int i = numberOfLilies - 2; i >= 0; i--)
    {
        int bestNextLily = QueryRMQ(i + 1, i + distLimit[i], lilyType[i]);
        maxJu[i] = juPerLily[i] - (bestNextLily - i) * lilyType[i] + maxJu[bestNextLily];

        for (int t = 1; t <= NumberOfLilyTypes; t++)
        {
            UpdateRMQ(i, t);
        }
    }
}

int main()
{
    Input();

    FillMaxJu();
    printf("%d\n", maxJu[0]);

    return 0;
}
