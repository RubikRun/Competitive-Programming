//Works

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define MaxNumberOfVertices 26

vector<int> children[MaxNumberOfVertices];
int numberOfVertices;

bool exists[MaxNumberOfVertices];

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
        exists[i] = true;
    }
}

int GetNextVertex()
{
    int nextVertex = MaxNumberOfVertices;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (!exists[i])
        {
            continue;
        }

        bool hasChildren = false;
        for (int j = 0; j < children[i].size(); j++)
        {
            if (exists[children[i][j]])
            {
                hasChildren = true;
                break;
            }
        }

        if (!hasChildren)
        {
            nextVertex = min(nextVertex, i);
        }
    }

    exists[nextVertex] = false;
    return nextVertex;
}

int main()
{
    Input();

    for (int i = 0; i < numberOfVertices; i++)
    {
        cout << (char)(GetNextVertex() + 'A');
    }
    cout << endl;

    return 0;
}
