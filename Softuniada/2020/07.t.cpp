#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXTOWNLEN 100
#define MAXTOWNCOUNT 1005
#define MAXPOSSIBLEFLOW 1000005

char towns[MAXTOWNCOUNT][MAXTOWNLEN];
int townsCount;

//probably needs to be initialized with 0s ?
int graph[MAXTOWNCOUNT][MAXTOWNCOUNT];

int GetTownIndex(char* town)
{
    for (int i = 0; i < townsCount; i++)
    {
        if (strcmp(town, towns[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool breadthFirstSearch(int grr[MAXTOWNCOUNT][MAXTOWNCOUNT], int s, int t, int upper[]) 
{ 
    bool used[MAXTOWNCOUNT]; 
    memset(used, 0, sizeof(used)); 
    queue <int> q; 
    q.push(s); 
    used[s] = true; 
    upper[s] = -1; 
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
  
        for (int i=0; i<townsCount; i++) 
        { 
            if (used[i]==false && grr[u][i] > 0) 
            { 
                q.push(i); 
                upper[i] = u; 
                used[i] = true; 
            } 
        } 
    } 
    return (used[t] == true); 
} 

int maxFlow(int s, int t) 
{ 
    int a, b; 
    int grr[MAXTOWNCOUNT][MAXTOWNCOUNT];  
    for (a = 0; a < townsCount; a++) 
        for (b = 0; b < townsCount; b++) 
             grr[a][b] = graph[a][b]; 
  
    int parent[MAXTOWNCOUNT];
  
    int res = 0;
    while (breadthFirstSearch(grr, s, t, parent)) 
    { 
        int path_flow = MAXPOSSIBLEFLOW; 
        for (b=t; b!=s; b=parent[b]) 
        { 
            a = parent[b]; 
            path_flow = min(path_flow, grr[a][b]); 
        }  
        for (b=t; b != s; b=parent[b]) 
        { 
            a = parent[b]; 
            grr[a][b] -= path_flow; 
            grr[b][a] += path_flow; 
        } 
        res += path_flow; 
    } 
    return res; 
} 

int main()
{
    cin >> towns[0] >> towns[1];
    townsCount = 2;

    int edgesCount;
    cin >> edgesCount;
    for (int i = 0; i < edgesCount; i++)
    {
        char townA[MAXTOWNLEN], townB[MAXTOWNLEN];
        cin >> townA >> townB;
        int capacity;
        cin >> capacity;

        int townAIndex = GetTownIndex(townA), townBIndex = GetTownIndex(townB);
        if (townAIndex == -1)
        {
            strcpy(towns[townsCount], townA);
            townAIndex = townsCount++;
        }
        if (townBIndex == -1)
        {
            strcpy(towns[townsCount], townB);
            townBIndex = townsCount++;
        }

        graph[townAIndex][townBIndex] = capacity;
    }

    cout << maxFlow(0, 1) << endl;
    return 0;
}