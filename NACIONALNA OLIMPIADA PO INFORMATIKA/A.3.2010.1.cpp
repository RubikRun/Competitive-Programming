//checked - 50%

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
#define MaxNumberOfTowns 1000

int numberOfTowns;
int ticketPrice;
int radius;
int storePrice;

int revenue;

int numberOfFans[MaxNumberOfTowns];

vector< pair<int, int> > adjTowns[MaxNumberOfTowns];
vector<int> reachableTowns[MaxNumberOfTowns];

int ticketsToSell[MaxNumberOfTowns];

void Input()
{
    scanf("%d %d %d %d", &numberOfTowns, &ticketPrice, &radius, &storePrice);

    for (int i = 0; i < numberOfTowns; i++)
    {
        scanf("%d", &numberOfFans[i]);
    }

    int a, b, c;
    for (int i = 0; i < numberOfTowns - 1; i++)
    {
        scanf("%d %d %d", &a, &b, &c); a--; b--;
        adjTowns[a].push_back( {b, c} );
        adjTowns[b].push_back( {a, c} );
    }
}

void FindReachableTownsFor(int root)
{
    int dist[MaxNumberOfTowns];
    for (int i = 0; i < numberOfTowns; i++)
    {
        dist[i] = -1;
    }
    dist[root] = 0;

    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < adjTowns[a].size(); i++)
        {
            int b = adjTowns[a][i].first;
            int c = adjTowns[a][i].second;

            if (dist[b] == -1)
            {
                dist[b] = dist[a] + c;
                if (dist[b] < radius)
                {
                    q.push(b);
                }
            }
        }
    }

    for (int i = 0; i < numberOfTowns; i++)
    {
        if (i != root && dist[i] <= radius && dist[i] != -1)
        {
            reachableTowns[root].push_back(i);
        }
    }
}

void FindReachableTownsForAll()
{
    for (int i = 0; i < numberOfTowns; i++)
    {
        FindReachableTownsFor(i);
    }
}

void FindMaxRevenue()
{
    revenue = 0;

    while (true)
    {
        for (int i = 0; i < numberOfTowns; i++)
        {
            ticketsToSell[i] = numberOfFans[i];
            for (int j = 0; j < reachableTowns[i].size(); j++)
            {
                ticketsToSell[i] += numberOfFans[reachableTowns[i][j]];
            }
        }

        int bestTown = 0;
        for (int i = 1; i < numberOfTowns; i++)
        {
            if (ticketsToSell[i] > ticketsToSell[bestTown])
            {
                bestTown = i;
            }
        }

        int subRevenue = ticketsToSell[bestTown] * ticketPrice - storePrice;
        if (subRevenue <= 0)
        {
            break;
        }
        revenue += subRevenue;

        numberOfFans[bestTown] = 0;
        for (int i = 0; i < reachableTowns[bestTown].size(); i++)
        {
            numberOfFans[reachableTowns[bestTown][i]] = 0;
        }
    }
}

int main()
{
    Input();
    FindReachableTownsForAll();
    FindMaxRevenue();

    printf("%d\n", revenue);

    return 0;
}
