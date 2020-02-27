/*
ID: borisd22
TASK: agrinet
LANG: C++
*/

#include <fstream>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfFarms 100

ifstream fin ("agrinet.in");
ofstream fout ("agrinet.out");

int numberOfFarms;
int dist[MaxNumberOfFarms][MaxNumberOfFarms];

void Input()
{
	Read >> numberOfFarms;

	for (int i = 0; i < numberOfFarms; i++)
	{
		for (int j = 0; j < numberOfFarms; j++)
		{
			Read >> dist[i][j];
		}
	}
}

int GetFiberLength()
{
	int fiberLength = 0;

	bool connected[MaxNumberOfFarms];
	for (int i = 0; i < numberOfFarms; i++)
	{
		connected[i] = false;
	}

	int base = 0;
	connected[base] = true;

	for (int k = 0; k < numberOfFarms - 1; k++)
	{
		int a = -1, b = -1;
		for (int i = 0; i < numberOfFarms; i++)
		{
			if (!connected[i])
			{
				continue;
			}
			for (int j = 0; j < numberOfFarms; j++)
			{
				if (connected[j])
				{
					continue;
				}
				if (a == -1 || dist[i][j] < dist[a][b])
				{
					a = i;
					b = j;
				}
			}
		}

		fiberLength += dist[a][b];
		connected[b] = true;
	}

	return fiberLength;
}

int main()
{
	Input();
	Write << GetFiberLength() << endl;

	return 0;
}
