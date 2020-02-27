//checked - 100%

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define MaxNumberOfNodes 20000
#define MaxNumberOfQueries 50000
#define MaxLog 17

//Tree structure
vector<int> adj[MaxNumberOfNodes]; //adj[x] contains all nodes adjacent to x
int numberOfNodes;

//Diam structures
vector<int> diam; //All nodes from the diameter in order
bool fromDiam[MaxNumberOfNodes]; //fromDiam[i] answers the question "Is node i from the diam?" or alternatively "Is node i a root of a subtree?"
int diamInd[MaxNumberOfNodes]; //diamInd[i] is the index of node i in diam

int subtreeSkip[MaxNumberOfNodes][MaxLog]; //subtreeSkip[i][j] is a node from the same subtree as i that is 2^j steps upward

int queryAnswers[MaxNumberOfQueries];
int numberOfQueryAnswers;

void ReadTree()
{
    scanf("%d", &numberOfNodes);

    for (int i = 0; i < numberOfNodes; i++)
    {
        int adjCount;
        scanf("%d", &adjCount);

        for (int j = 0; j < adjCount; j++)
        {
            int newAdj;
            scanf("%d", &newAdj);
            newAdj--;

            adj[i].push_back(newAdj);
        }
    }
}

void FindLongestPath(int root, vector<int>& path)
{
    int dist[MaxNumberOfNodes], prev[MaxNumberOfNodes];
    for (int i = 0; i < numberOfNodes; i++)
    {
        dist[i] = -1;
        prev[i] = -1;
    }
    dist[root] = 0;

    int last = root;

    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < adj[a].size(); i++)
        {
            int b = adj[a][i];

            if (dist[b] != -1)
            {
                continue;
            }

            dist[b] = dist[a] + 1;
            prev[b] = a;

            if (dist[b] > dist[last])
            {
                last = b;
            }

            q.push(b);
        }
    }

    path.clear();
    while (last != -1)
    {
        path.push_back(last);
        last = prev[last];
    }
    reverse(path.begin(), path.end());
}

void FindDiam()
{
    int r = 0;
    FindLongestPath(r, diam);
    int a = diam.back();
    FindLongestPath(a, diam);

    for (int i = 0; i < numberOfNodes; i++)
    {
        fromDiam[i] = false;
        diamInd[i] = -1;
    }
    for (int i = 0; i < diam.size(); i++)
    {
        fromDiam[diam[i]] = true;
        diamInd[diam[i]] = i;
    }
}

void FillSubtreeSkip()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        subtreeSkip[i][0] = -1;
    }
    for (int i = 0; i < numberOfNodes; i++)
    {
        if (!fromDiam[i])
        {
            continue;
        }

        queue<int> q;
        q.push(i);
        while (!q.empty())
        {
            int a = q.front();
            q.pop();

            for (int j = 0; j < adj[a].size(); j++)
            {
                int b = adj[a][j];
                if (fromDiam[b] || b == i || subtreeSkip[b][0] != -1)
                {
                    continue;
                }

                subtreeSkip[b][0] = a;
                q.push(b);
            }
        }
    }

    for (int j = 1; j < MaxLog; j++)
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            subtreeSkip[i][j] = (subtreeSkip[i][j - 1] == -1) ? -1 : subtreeSkip[subtreeSkip[i][j - 1]][j - 1];
        }
    }
}

void AnswerQuery(int root, int dist)
{
    int largestSkip = 1, largestPower = 0;
    while (largestSkip * 2 <= dist)
    {
        largestSkip *= 2;
        largestPower++;
    }

    if (fromDiam[root])
    {
        if (diamInd[root] >= dist)
        {
            queryAnswers[numberOfQueryAnswers++] = diam[diamInd[root] - dist] + 1;
        }
        else if (diam.size() - 1 - diamInd[root] >= dist)
        {
            queryAnswers[numberOfQueryAnswers++] = diam[diamInd[root] + dist] + 1;
        }
        else
        {
            queryAnswers[numberOfQueryAnswers++] = 0;
        }
    }
    else
    {
        int x = root;
        int distLeft = dist;
        int currSkip = largestSkip;
        int currPower = largestPower;

        while (subtreeSkip[x][0] != -1 && distLeft > 0)
        {
            while (subtreeSkip[x][currPower] == -1)
            {
                currSkip /= 2;
                currPower--;
            }

            distLeft -= currSkip;
            x = subtreeSkip[x][currPower];

            while (currSkip > distLeft)
            {
                currSkip /= 2;
                currPower--;
            }
        }
        if (distLeft == 0)
        {
            queryAnswers[numberOfQueryAnswers++] = x + 1;
            return;
        }

        AnswerQuery(x, distLeft);
        return;
    }
}

void DoQueries()
{
    int numberOfQueries;
    scanf("%d", &numberOfQueries);
    numberOfQueryAnswers = 0;

    for (int i = 0; i < numberOfQueries; i++)
    {
        int root, dist;
        scanf("%d %d", &root, &dist);
        root--;

        AnswerQuery(root, dist);
    }
}

int main()
{
    ReadTree();
    FindDiam();
    FillSubtreeSkip();

    DoQueries();

    for (int i = 0; i < numberOfQueryAnswers; i++)
    {
        printf("%d\n", queryAnswers[i]);
    }

    return 0;
}
