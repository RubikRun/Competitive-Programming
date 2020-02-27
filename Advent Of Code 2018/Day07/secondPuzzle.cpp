//Works

#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
#define MaxNumberOfVertices 26
#define NumberOfWorkers 5

vector<int> children[MaxNumberOfVertices];
int numberOfVertices;

int workLeft[NumberOfWorkers];
int worksOn[NumberOfWorkers];
int state[MaxNumberOfVertices];
int numberOfDoneVertices;

void Input()
{
    numberOfVertices = 0;

    while (true)
    {
        string input;
        getline(cin, input);

        if (input == "end")
        {
            break;
        }

        int a = input[36] - 'A';
        int b = input[5] - 'A';

        children[a].push_back(b);
        numberOfVertices = max(numberOfVertices, a + 1);
        numberOfVertices = max(numberOfVertices, b + 1);
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        state[i] = 0;
    }
    numberOfDoneVertices = 0;
    for (int i = 0; i < NumberOfWorkers; i++)
    {
        workLeft[i] = 0;
        worksOn[i] = -1;
    }
}

void SecondPass()
{
    for (int freeWorker = 0; freeWorker < NumberOfWorkers; freeWorker++)
    {
        if (worksOn[freeWorker] != -1)
        {
            continue;
        }

        int nextVertex = MaxNumberOfVertices;
        for (int vertex = 0; vertex < numberOfVertices; vertex++)
        {
            if (state[vertex] != 0)
            {
                continue;
            }

            bool hasChildren = false;
            for (int childIndex = 0; childIndex < children[vertex].size(); childIndex++)
            {
                int child = children[vertex][childIndex];
                if (state[child] != 2)
                {
                    hasChildren = true;
                    break;
                }
            }

            if (!hasChildren)
            {
                nextVertex = min(nextVertex, vertex);
            }
        }

        if (nextVertex == MaxNumberOfVertices)
        {
            break;
        }

        state[nextVertex] = 1;
        workLeft[freeWorker] = nextVertex + 61;
        worksOn[freeWorker] = nextVertex;
    }

    for (int busyWorker = 0; busyWorker < NumberOfWorkers; busyWorker++)
    {
        if (worksOn[busyWorker] == -1)
        {
            continue;
        }

        workLeft[busyWorker]--;
        if (workLeft[busyWorker] == 0)
        {
            state[worksOn[busyWorker]] = 2;
            worksOn[busyWorker] = -1;
            numberOfDoneVertices++;
        }
    }
}

int main()
{
    Input();

    for (int seconds = 1; true; seconds++)
    {
        SecondPass();
        if (numberOfDoneVertices == numberOfVertices)
        {
            cout << seconds << endl;
            return 0;
        }
    }
}
