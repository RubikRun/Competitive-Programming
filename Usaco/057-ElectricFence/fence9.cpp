/*
ID: borisd22
TASK: fence9
LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;
#define Read fin
#define Write fout

ifstream fin ("fence9.in");
ofstream fout ("fence9.out");

int main()
{
	int n, m, p;
	fin >> n >> m >> p;
	int r = 0;
	if (p >= n)
	{
		for (int i = 1; i < m; i++)
		{
			int left = (i * n) / m + 1;
			int right = p - (i * (p - n)) / m - 1;
			r += right - left + 1;
		}
	}
	else
	{
		for (int i = 1; i < m; i++)
		{
			int left = (i * n) / m + 1;
			int right;
			if ((i * (n - p)) % m == 0)
			{
				right = p + (i * (n - p)) / m - 1;
			}
			else
			{
				right = p + (i * (n - p)) / m;
			}
			r += right - left + 1;
		}
	}
	fout << r << endl;
	return 0;
}