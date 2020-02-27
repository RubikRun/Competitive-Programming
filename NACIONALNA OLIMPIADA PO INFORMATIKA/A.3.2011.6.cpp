//checked - 100%

#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;
#define MaxMountainSize 10000

char mountain[MaxMountainSize];
int mountainSize;

void Input()
{
    scanf("%s", mountain);
    mountainSize = strlen(mountain);
}

int main()
{
    Input();

    int water = 0;

    stack<int> downs;
    stack< pair<int, int> > lakes;
    for (int i = 0; i < mountainSize; i++)
    {
        if (mountain[i] == '\\')
        {
            downs.push(i);
        }
        else if (mountain[i] == '/')
        {
            if (!downs.empty())
            {
                water += i - downs.top();

                pair<int, int> newLake = {downs.top(), i};
                while (!lakes.empty() && lakes.top().first > newLake.first && lakes.top().second < newLake.second)
                {
                    lakes.pop();
                }
                lakes.push(newLake);

                downs.pop();
            }
        }
    }

    printf("%lu %d\n", lakes.size(), water);

    return 0;
}
