//checked - 25%

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
#define MaxCodeSize 2000

char code[MaxCodeSize + 1];
int codeSize;

vector<char> minNum[MaxCodeSize + 1];

void Input()
{
	scanf("%s", code);
	codeSize = strlen(code);
}

void FillMinNum()
{
	minNum[codeSize] = {'0'};

	for (int i = codeSize - 1; i >= 0; i--)
	{
		bool found[10]; for (int k = 0; k < 10; k++) found[k] = false;
		for (int k = i; k < codeSize; k++) found[code[k] - '0'] = true;
		for (int k = (i == 0); k < 10; k++) { if (!found[k]) {minNum[i] = {(char)(k + '0')}; break;} }
		if (!minNum[i].empty()) continue;


		for (char d = (i == 0) + '0'; d <= '9'; d++)
		{
			int x = i;
			while (code[x] != d && x < codeSize) x++;
			if (code[x] != d) continue;

			if (minNum[i].empty() || minNum[x + 1].size() + 1 < minNum[i].size())
			{
				minNum[i] = minNum[x + 1];
				minNum[i].insert(minNum[i].begin(), code[x]);
			}
		}
	}
}

int main()
{
	Input();
	FillMinNum();

	for (int i = 0; i < minNum[0].size(); i++)
	{
		printf("%c", minNum[0][i]);
	}
	printf("\n");

	return 0;
}
