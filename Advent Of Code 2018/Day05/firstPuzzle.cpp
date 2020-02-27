//Works

#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;
#define MaxStringSize 50000

char ConvertType(char x) { return (x >= 'a' && x <= 'z') ? (x - 'a' + 'A') : (x - 'A' + 'a'); }

int main()
{
    char original[MaxStringSize + 1];
    scanf("%s", original);

    stack<char> reacted;
    for (int i = 0; i < strlen(original); i++)
    {
        if (reacted.empty() || reacted.top() != ConvertType(original[i]))
        {
            reacted.push(original[i]);
        }
        else
        {
            reacted.pop();
        }
    }

    printf("%lu\n", reacted.size());

    return 0;
}
