/*
ID: borisd22
TASK: inflate
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MAXN 10000

ifstream fin ("inflate.in");
ofstream fout ("inflate.out");

int main()
{
	int m, n;
	Read >> m >> n;

	int p[MAXN], s[MAXN];
	for(int i = 0; i < n; i++)
	{
		Read >> p[i] >> s[i];
	}

	int f[MAXN + 1];
	f[0] = 0;

	for (int i = 1; i <= m; i++)
	{
		f[i] = 0;
		for (int j = 0; j < n; j++)
		{
			if (i - s[j] >= 0)
			{
				f[i] = max(f[i], f[i - s[j]] + p[j]);
			}
		}
	}

	Write << f[m] << endl;

	return 0;
}
