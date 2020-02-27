//checked - 100%

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MaxExprLen 29

#define MaxExprValue 1000000000000000000
#define MinExprValue -1000000000000000000


char expr[MaxExprLen];
int exprLen;

void Input()
{
    scanf("%s",expr);
    exprLen = (int)strlen(expr);
}

long long subExprMin[MaxExprLen][MaxExprLen];
long long subExprMax[MaxExprLen][MaxExprLen];
bool subExprDone[MaxExprLen][MaxExprLen];

void InitTables()
{
    for (int i = 0; i < exprLen; i++)
    {
        for (int j = 0; j < exprLen; j++)
        {
            subExprDone[i][j] = false;
        }
    }
}

void CalcSubExpr(int first, int last)
{
    if (first == last)
    {
        subExprMin[first][last] = expr[first] - '0';
        subExprMax[first][last] = expr[first] - '0';
        subExprDone[first][last] = true;

        return;
    }

    long long minValue = MaxExprValue;
    long long maxValue = MinExprValue;
    for (int cut = first + 1; cut < last; cut += 2)
    {
        if (!subExprDone[first][cut - 1])
        {
            CalcSubExpr(first, cut - 1);
        }
        if (!subExprDone[cut + 1][last])
        {
            CalcSubExpr(cut + 1, last);
        }

        if (expr[cut] == '+')
        {
            minValue = min(minValue, subExprMin[first][cut - 1] + subExprMin[cut + 1][last]);
            maxValue = max(maxValue, subExprMax[first][cut - 1] + subExprMax[cut + 1][last]);
        }
        else if (expr[cut] == '*')
        {
            minValue = min(minValue, subExprMin[first][cut - 1] * subExprMin[cut + 1][last]);
            minValue = min(minValue, subExprMin[first][cut - 1] * subExprMax[cut + 1][last]);
            minValue = min(minValue, subExprMax[first][cut - 1] * subExprMin[cut + 1][last]);
            minValue = min(minValue, subExprMax[first][cut - 1] * subExprMax[cut + 1][last]);
            maxValue = max(maxValue, subExprMax[first][cut - 1] * subExprMax[cut + 1][last]);
            maxValue = max(maxValue, subExprMin[first][cut - 1] * subExprMax[cut + 1][last]);
            maxValue = max(maxValue, subExprMax[first][cut - 1] * subExprMin[cut + 1][last]);
            maxValue = max(maxValue, subExprMin[first][cut - 1] * subExprMin[cut + 1][last]);
        }
        else
        {
            minValue = min(minValue, subExprMin[first][cut - 1] - subExprMax[cut + 1][last]);
            maxValue = max(maxValue, subExprMax[first][cut - 1] - subExprMin[cut + 1][last]);
        }
    }

    subExprMin[first][last] = minValue;
    subExprMax[first][last] = maxValue;
    subExprDone[first][last] = true;
}

int main()
{
    Input();
    InitTables();
    CalcSubExpr(0, exprLen - 1);

    printf("%lld\n", subExprMin[0][exprLen - 1]);

    return 0;
}