//checked - 100%

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define MaxNumberOfTowers 14999

struct Tower
{
    int position;
    int height;
};

Tower towers[MaxNumberOfTowers];
int numberOfTowers;

int maxDist;

vector<int> reachable[MaxNumberOfTowers];
int dist[MaxNumberOfTowers];

void Input()
{
    scanf("%d", &numberOfTowers);
    scanf("%d", &maxDist);

    for (int i = 0; i < numberOfTowers; i++)
    {
        scanf("%d %d", &towers[i].position, &towers[i].height);
    }
}

bool BlocksView(int m, int a, int b)
{
    return (towers[b].position - towers[a].position) * (towers[m].height - towers[a].height)
    >= (towers[b].height - towers[a].height) * (towers[m].position - towers[a].position);
}

bool CanSee(int a, int b)
{
    for (int i = a + 1; i <= b - 1; i++)
    {
        if (BlocksView(i, a, b))
        {
            return false;
        }
    }

    return true;
}

void FillReachable()
{
    for (int i = 0; i < numberOfTowers - 1; i++)
    {
        reachable[i].push_back(i + 1);
        for (int j = i + 2; j < numberOfTowers && towers[j].position - towers[i].position <= maxDist; j++)
        {
            if (CanSee(i, j))
            {
                reachable[i].push_back(j);
            }
        }
    }
}

int GetMinNumberOfCams()
{
    for (int i = 0; i < numberOfTowers; i++)
    {
        dist[i] = -1;
    }
    dist[0] = 0;

    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int currTower = q.front();
        q.pop();

        for (int i = 0; i < reachable[currTower].size(); i++)
        {
            int nextTower = reachable[currTower][i];

            if (dist[nextTower] == -1)
            {
                dist[nextTower] = dist[currTower] + 1;
                q.push(nextTower);
            }
        }
    }

    return dist[numberOfTowers - 1] + 1;
}

int main()
{
    Input();
    FillReachable();

    printf("%d\n", GetMinNumberOfCams());

    return 0;
}

