//checked - 100%

#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

#define MaxNumberOfBrackets 40

void Solve()
{
    char brackets[MaxNumberOfBrackets + 1];
    scanf("%s", brackets);
    int numberOfBrackets = (int)strlen(brackets);

    bool roundBracketPassed = false;
    stack<char> openBrackets;
    for (int i = 0; i < numberOfBrackets; i++)
    {
        if (brackets[i] == '(')
        {
            if (openBrackets.empty() || (openBrackets.size() == 1 && openBrackets.top() == '['))
            {
                openBrackets.push(brackets[i]);
                roundBracketPassed = true;
            }
            else
            {
                printf("0\n");
                return;
            }
        }
        else if (brackets[i] == ')')
        {
            if (!openBrackets.empty() && openBrackets.top() == '(')
            {
                openBrackets.pop();
            }
            else
            {
                printf("0\n");
                return;
            }
        }
        else if (brackets[i] == '[')
        {
            if (openBrackets.empty())
            {
                openBrackets.push(brackets[i]);
                roundBracketPassed = false;
            }
            else
            {
                printf("0\n");
                return;
            }
        }
        else
        {
            if (!openBrackets.empty() &&openBrackets.top() == '[' && roundBracketPassed)
            {
                openBrackets.pop();
            }
            else
            {
                printf("0\n");
                return;
            }
        }
    }

    printf("1\n");
}

int main()
{
    Solve();
    Solve();
    Solve();
    Solve();
}