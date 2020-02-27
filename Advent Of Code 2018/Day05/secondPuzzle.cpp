//Works

#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;
#define MaxStringSize 50000

char ConvertType(char x) { return (x >= 'a' && x <= 'z') ? (x - 'a' + 'A') : (x - 'A' + 'a'); }

char original[MaxStringSize + 1];
int originalSize;

void Input()
{
    scanf("%s", original);
    originalSize = strlen(original);
}

int GetReactedSize(char problem)
{
    stack<char> reacted;
    for (int i = 0; i < originalSize; i++)
    {
        if (original[i] == problem || original[i] == ConvertType(problem))
        {
            continue;
        }

        if (reacted.empty() || reacted.top() != ConvertType(original[i]))
        {
            reacted.push(original[i]);
        }
        else
        {
            reacted.pop();
        }
    }

    return reacted.size();
}

int main()
{
    Input();

    int bestReactedSize = originalSize;
    for (char problem = 'a'; problem <= 'z'; problem++)
    {
        bestReactedSize = min(bestReactedSize, GetReactedSize(problem));
    }

    printf("%d\n", bestReactedSize);

    return 0;
}
