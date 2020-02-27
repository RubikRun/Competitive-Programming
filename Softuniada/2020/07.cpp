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

void InitGraph()
{
    for (int i = 0; i < MAXTOWNCOUNT; i++)
    {
        for (int j = 0; j < MAXTOWNCOUNT; j++)
        {
            graph[i][j] = 0;
        }
    }
}

bool bfs(int rGraph[MAXTOWNCOUNT][MAXTOWNCOUNT], int s, int t, int parent[]) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[MAXTOWNCOUNT]; 
    memset(visited, 0, sizeof(visited)); 
  
    // Create a queue, enqueue source vertex and mark source vertex 
    // as visited 
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
  
    // Standard BFS Loop 
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
  
        for (int v=0; v<townsCount; v++) 
        { 
            if (visited[v]==false && rGraph[u][v] > 0) 
            { 
                q.push(v); 
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 
  
    // If we reached sink in BFS starting from source, then return 
    // true, else false 
    return (visited[t] == true); 
} 

// Returns the maximum flow from s to t in the given graph 
int fordFulkerson(int s, int t) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    int rGraph[MAXTOWNCOUNT][MAXTOWNCOUNT]; // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < townsCount; u++) 
        for (v = 0; v < townsCount; v++) 
             rGraph[u][v] = graph[u][v]; 
  
    int parent[MAXTOWNCOUNT];  // This array is filled by BFS and to store path 
  
    int max_flow = 0;  // There is no flow initially 
  
    // Augment the flow while tere is path from source to sink 
    while (bfs(rGraph, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = MAXPOSSIBLEFLOW; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
  
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
  
    // Return the overall flow 
    return max_flow; 
} 

int main()
{
    cin >> towns[0] >> towns[1];
    townsCount = 2;

    InitGraph();
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

    cout << fordFulkerson(0, 1) << endl;
    return 0;
}