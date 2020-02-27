/*
ID: borisd22
TASK: heritage
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <unordered_map>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfNodes 26

ifstream fin ("heritage.in");
ofstream fout ("heritage.out");

char inOrder[MaxNumberOfNodes + 1];
char preOrder[MaxNumberOfNodes + 1];
int numberOfNodes;

unordered_map<char, char> leftChild;
unordered_map<char, char> rightChild;

void Input()
{
	Read >> inOrder >> preOrder;

	numberOfNodes = (int)strlen(inOrder);
}

void BuildTree(int inOrderFirst, int inOrderLast, int preOrderFirst)
{
	if (inOrderFirst > inOrderLast)
	{
		return;
	}

	char currRoot = preOrder[preOrderFirst];

	int rootInOrderIndex = inOrderFirst;
	while (inOrder[rootInOrderIndex] != currRoot)
	{
		rootInOrderIndex++;
	}

	if (rootInOrderIndex > inOrderFirst)
	{
		leftChild[currRoot] = preOrder[preOrderFirst + 1];
	}
	if (rootInOrderIndex < inOrderLast)
	{
		rightChild[currRoot] = preOrder[preOrderFirst + rootInOrderIndex - inOrderFirst + 1];
	}

	BuildTree(inOrderFirst, rootInOrderIndex - 1, preOrderFirst + 1);
	BuildTree(rootInOrderIndex + 1, inOrderLast, preOrderFirst + rootInOrderIndex - inOrderFirst + 1);	
}

void PrintPostOrder(char currRoot)
{
	if (leftChild.count(currRoot) > 0) PrintPostOrder(leftChild[currRoot]);
	if (rightChild.count(currRoot) > 0) PrintPostOrder(rightChild[currRoot]);
	Write << currRoot;
}

int main()
{
	Input();

	BuildTree(0, numberOfNodes - 1, 0);
	PrintPostOrder(preOrder[0]);
	Write << endl;

	return 0;
}