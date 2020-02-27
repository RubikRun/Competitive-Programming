//checked - 100%

#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;
#define MaxNumberOfVertices 1000

int numberOfVertices;
int numberOfEdges;

vector<int> children[MaxNumberOfVertices];

int weight[MaxNumberOfVertices][MaxNumberOfVertices];
int firstWeight, lastWeight;

vector<int> topSort;
bool inTopSort[MaxNumberOfVertices];

int state[MaxNumberOfVertices];

int radiation;

void Input()
{
    scanf("%d %d", &numberOfVertices, &numberOfEdges);

    firstWeight = 1 << 30;
    lastWeight = 0;
    int a, b, w;
    for (int i = 0; i < numberOfEdges; i++)
    {
        scanf("%d %d %d", &a, &b, &w);
        a--;
        b--;

        children[a].push_back(b);
        weight[a][b] = w;
        firstWeight = min(firstWeight, w);
        lastWeight = max(lastWeight, w);
    }
}

bool DFS(int root)
{
    state[root] = 1;

    for (int i = 0; i < children[root].size(); i++)
    {
        int child = children[root][i];
        if (weight[root][child] > radiation) continue;
        if (state[child] == 2) continue;
        if (state[child] == 1) return false;
        if (!DFS(child)) return false;
    }

    state[root] = 2;
    return true;
}

bool HasLoops()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        state[i] = 0;
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (state[i] == 2) continue;
        if (!DFS(i))
        {
            return true;
        }
    }

    return false;
}

void FindTopSort()
{
    topSort.clear();

    for (int i = 0; i < numberOfVertices; i++)
    {
        inTopSort[i] = false;
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        int best = MaxNumberOfVertices;
        for (int j = 0; j < numberOfVertices; j++)
        {
            if (inTopSort[j]) continue;

            bool hasConnectedChildren = false;
            for (int k = 0; k < children[j].size(); k++)
            {
                if (weight[j][children[j][k]] <= radiation && !inTopSort[children[j][k]])
                {
                    hasConnectedChildren = true;
                    break;
                }
            }
            if (hasConnectedChildren) continue;

            best = min(best, j);
        }

        topSort.push_back(best);
        inTopSort[best] = true;
    }
}

int main()
{
    Input();

    radiation = lastWeight;
    if (!HasLoops())
    {
        FindTopSort();
        printf("-1\n");
        for (int i = 0; i < numberOfVertices - 1; i++)
        {
            printf("%d ", topSort[i] + 1);
        }
        printf("%d\n", topSort.back() + 1);

        return 0;
    }

    while (firstWeight <= lastWeight)
    {
        radiation = (firstWeight + lastWeight) / 2 + 1;
        bool b2 = !HasLoops();
        radiation--;
        bool b1 = !HasLoops();

        if (b1 && !b2)
        {
            break;
        }

        if (!b1)
        {
            lastWeight = radiation - 1;
        }
        else
        {
            firstWeight = radiation + 1;
        }
    }
    FindTopSort();

    printf("%d\n", radiation);
    for (int i = 0; i < numberOfVertices - 1; i++)
    {
        printf("%d ", topSort[i] + 1);
    }
    printf("%d\n", topSort.back() + 1);

    return 0;
}
