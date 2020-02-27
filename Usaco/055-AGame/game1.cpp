/*
ID: borisd22
TASK: game1
LANG: C++
*/

#include <fstream>

using namespace std;
#define MaxSeqSize 100
#define Read fin
#define Write fout

ifstream fin ("game1.in");
ofstream fout ("game1.out");

int seq[MaxSeqSize];
pair<int, int> results[MaxSeqSize][MaxSeqSize];
int seqSize;

void Input()
{
	Read >> seqSize;

	for (int i = 0; i < seqSize; i++)
	{
		Read >> seq[i];
	}
}

void FillResults()
{
	for (int i = 0; i < seqSize; i++)
	{
		results[i][i] = {seq[i], 0};
	}

	for (int subSeqSize = 2; subSeqSize <= seqSize; subSeqSize++)
	{
		for (int i = 0; i + subSeqSize - 1 < seqSize; i++)
		{
			int j = i + subSeqSize - 1;

			pair<int, int> A = {results[i + 1][j].second + seq[i], results[i + 1][j].first};
			pair<int, int> B = {results[i][j - 1].second + seq[j], results[i][j - 1].first};

			if (A.first - A.second > B.first - B.second)
			{
				results[i][j] = A;
			}
			else
			{
				results[i][j] = B;
			}
		}
	}
}

int main()
{
	Input();

	FillResults();
	Write << results[0][seqSize - 1].first << " " << results[0][seqSize - 1].second << endl;

	return 0;
}