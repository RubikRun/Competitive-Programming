/*
ID: borisd22
TASK: range
LANG: C++
*/

#include <fstream>

using namespace std;
#define Read fin
#define Write fout
#define MaxMatrixSize 250

ifstream fin ("range.in");
ofstream fout ("range.out");

char matrix[MaxMatrixSize + 1][MaxMatrixSize + 1];
int matrixSize;

int ones[MaxMatrixSize][MaxMatrixSize];

void Input()
{
	Read >> matrixSize;

	for (int i = 0; i < matrixSize; i++)
	{
		Read >> matrix[i];
	}
}

void FillOnes()
{
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			ones[i][j] = matrix[i][j] - '0';
			if (i > 0) ones[i][j] += ones[i - 1][j];
			if (j > 0) ones[i][j] += ones[i][j - 1];
			if (i > 0 && j > 0) ones[i][j] -= ones[i - 1][j - 1];
		}
	}
}

int GetOnes(int a, int b, int c, int d)
{
	int result = ones[c][d];
	if (a > 0) result -= ones[a - 1][d];
	if (b > 0) result -= ones[c][b - 1];
	if (a > 0 && b > 0) result+= ones[a - 1][b - 1];

	return result;
}

int GetNumberOfSquares(int squareSize)
{
	int numberOfSquares = 0;

	for (int i = 0; i + squareSize - 1 < matrixSize; i++)
	{
		for (int j = 0; j + squareSize - 1 < matrixSize; j++)
		{
			if (GetOnes(i, j, i + squareSize - 1, j + squareSize - 1) == squareSize * squareSize)
			{
				numberOfSquares++;
			}
		}
	}

	return numberOfSquares;
}

int main()
{
	Input();
	FillOnes();

	for (int i = 2; i <= matrixSize; i++)
	{
		int numberOfSquares = GetNumberOfSquares(i);
		if (numberOfSquares > 0)
		{
			Write << i << " " << numberOfSquares << endl;
		}
	}

	return 0;
}