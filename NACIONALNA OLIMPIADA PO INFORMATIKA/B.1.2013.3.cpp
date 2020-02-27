//checked - 100%

#include <cstdio>
#include <queue>
using namespace std;

#define MAXP 1000000

int P, A, B, R;
int level[MAXP];

void InitLevelArray()
{
    for (int i = 0; i < P; i++)
    {
        level[i] = 0;
    }
}

void FillLevelArray(int N)
{
    queue<int> q;
    q.push(N);

    int currentN, nextNA,nextNB;
    while (!q.empty())
    {
        currentN = q.front(); q.pop();

        if (currentN == R && level[currentN] != 0)
        {
            break;
        }

        nextNA = (currentN + A) % P;
        if (level[nextNA] == 0)
        {
            level[nextNA] = level[currentN] + 1;
            q.push(nextNA);
        }

        nextNB = (currentN + B) % P;
        if (level[nextNB] == 0)
        {
            level[nextNB] = level[currentN] + 1;
            q.push(nextNB);
        }
    }
}

int main()
{
    int N;
    scanf("%d%d%d%d%d", &N, &P, &A, &B, &R);

    InitLevelArray();
    FillLevelArray(N % P);

    if (level[R] != 0)
    {
        printf("%d\n", level[R]);
    }
    else
    {
        printf("-1\n");
    }

    return 0;
}