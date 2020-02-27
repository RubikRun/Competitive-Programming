//checked - 100%

#include <cstdio>

using namespace std;
#define MaxNumberOfElements 1000000
#define MaxSegmentTreeSize 2097152

int invTable[MaxNumberOfElements];
int permutation[MaxNumberOfElements];
int numberOfElements;

int segmentTree[MaxSegmentTreeSize];
int segmentTreeSize;

void Input()
{
	scanf("%d", &numberOfElements);

	for (int i = 0; i < numberOfElements; i++)
	{
		scanf("%d", &invTable[i]);
	}
}

void CreateSegmentTree()
{
	segmentTreeSize = 1;
	while (segmentTreeSize / 2 < numberOfElements)
	{
		segmentTreeSize *= 2;
	}

	int levelA = 1, levelB = 1;
	int levelVal = segmentTreeSize / 2;
	for (int i = 1; i < segmentTreeSize; i++)
	{
		segmentTree[i] = levelVal;

		if (i == levelB)
		{
			levelA = levelB + 1;
			levelB = levelA * 2 - 1;
			levelVal /= 2;
		}
	}
}

void UpdateValueInSegmentTree(int pos, int val)
{
	pos += segmentTreeSize / 2;
	int delta = val - segmentTree[pos];

	while (pos >= 1)
	{
		segmentTree[pos] += delta;
		pos /= 2;
	}
}

int GetPositionFromSegmentTree(int pos)
{
	int currNode = 1, sumLeft = pos + 1;

	while (currNode < segmentTreeSize / 2)
	{
		if (segmentTree[currNode * 2] >= sumLeft)
		{
			currNode *= 2;
		}
		else
		{
			sumLeft -= segmentTree[currNode * 2];
			currNode = currNode * 2 + 1;
		}
	}

	return currNode - segmentTreeSize / 2;
}

void FindPermutation()
{
	for (int i = 0; i < numberOfElements; i++)
	{
		int pos = GetPositionFromSegmentTree(invTable[i]);
		permutation[pos] = i;
		UpdateValueInSegmentTree(pos, 0);
	}
}

int main()
{
	Input();

	CreateSegmentTree();
	FindPermutation();
	for (int i = 0; i < numberOfElements; i++)
	{
		printf("%d\n", permutation[i] + 1);
	}

	return 0;
}