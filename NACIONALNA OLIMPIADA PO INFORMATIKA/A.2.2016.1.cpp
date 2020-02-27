//correctness - 100%
//spped - 70-80%

#include <cstdio>
#include <stack>
#include <cstring>
#include <map>

using namespace std;
#define MaxExprLen 1000
#define MaxNumOfVars 26

char expr[MaxExprLen];
int exprLen;

char varValues[MaxNumOfVars];
int numOfVars;

char Func(char x, char y) { return '0' + ((x == '0') || (y == '0')); }

char GetVarValueAt(int x)
{
	return varValues[expr[x] - 'a'];
}

char GetExprValue()
{
	char value;
	stack<char> s;

	value = 'e';
	for (int i = 0; i < exprLen; i++)
	{
		if (expr[i] == '(')
		{
			s.push(value);
			value = 'e';
		}
		else if (expr[i] == ')')
		{
			if (s.top() != 'e' && value != 'e')
			{
				value = Func(value, s.top());
			}
			s.pop();
		}
		else
		{
			if (value == 'e')
			{
				value = GetVarValueAt(i);
			}
			else
			{
				value = Func(value, GetVarValueAt(i));
			}
		}
	}

	return value;
}

void SimplifyExpr()
{
	numOfVars = 0;

	bool letterFound[MaxNumOfVars]; for (int i = 0; i < MaxNumOfVars; i++) letterFound[i] = false;
	for (int i = 0; i < exprLen; i++)
	{
		if (expr[i] != '(' && expr[i] != ')' && !letterFound[expr[i] - 'a'])
		{
			letterFound[expr[i] - 'a'] = true;
			numOfVars++;
		}
	}

	map<char, char> letterMap;
	char x = 'a';
	for (int i = 0; i < MaxNumOfVars; i++)
	{
		if (letterFound[i])
		{
			letterMap['a' + i] = x++;
		}
	}

	for (int i = 0; i < exprLen; i++)
	{
		if (expr[i] != '(' && expr[i] != ')')
		{
			expr[i] = letterMap[expr[i]];
		}
	}
}

void Input()
{
	scanf("%s", expr);
	exprLen = strlen(expr);
	SimplifyExpr();
}

int main()
{
	Input();

	while (true)
	{
		scanf("%s", varValues);
		if (varValues[0] == '2')
		{
			break;
		}
		printf("%c", GetExprValue());
	}

	printf("\n");	

	return 0;
}
