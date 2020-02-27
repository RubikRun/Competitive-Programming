//checked - 50%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MaxNumberOfElements 100000
#define MaxGroupSize 500000

int elements[MaxNumberOfElements];
int numberOfElements;

int groupSize;

int table[MaxGroupSize][MaxNumberOfElements / MaxGroupSize + 1];
int numberOfCols[MaxGroupSize];

void Input()
{
	scanf("%d %d", &numberOfElements, &groupSize);

	for (int i = 0; i < numberOfElements; i++)
	{
		scanf("%d", &elements[i]);
		elements[i]--;
	}
}

bool EveryElementCanGoHome()
{
	for (int i = 0; i < numberOfElements; i++)
	{
		if ((elements[i] - i) % groupSize != 0)
		{
			return false;
		}
	}

	return true;
}

void FillTable()
{
	for (int i = 0; i < groupSize; i++)
	{
		numberOfCols[i] = 0;
	}
	for (int i = 0; i < numberOfElements; i++)
	{
		table[i % groupSize][i / groupSize] = elements[i];
		numberOfCols[i % groupSize] = max(numberOfCols[i % groupSize], i / groupSize + 1);
	}
}

int GetNumberOfInversions(int row)
{
	int numberOfInversions = 0;

	for (int i = 0; i < numberOfCols[row] - 1; i++)
	{
		for (int j = i + 1; j < numberOfCols[row]; j++)
		{
			if (table[row][i] > table[row][j])
			{
				numberOfInversions++;
			}
		}
	}
}

bool AllRowsInversionsAreSameMod2()
{
	int mod2 = GetNumberOfInversions(0) % 2;
	for (int i = 1; i < groupSize; i++)
	{
		if (GetNumberOfInversions(i) % 2 != mod2)
		{
			return false;
		}
	}
	return true;
}

void SortAllRows()
{
	for (int i = 0; i < groupSize; i++)
	{
		sort(table[i], table[i] + numberOfCols[i]);
	}
}

bool TableIsSorted()
{
	for (int i = 1; i < numberOfElements; i++)
	{
		if (table[i % groupSize][i / groupSize] > table[(i - 1) % groupSize][(i - 1) / groupSize])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	#define AnswerYes printf("1\n"); return 0;
	#define AnswerNo printf("0\n"); return 0;

	Input();

	if (!EveryElementCanGoHome() || !AllRowsInversionsAreSameMod2())
	{
		AnswerNo
	}

	SortAllRows();
	if (TableIsSorted())
	{
		AnswerYes
	}
	else
	{
		AnswerNo
	}
}