//checked - 100%

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 1000

int n;

int nPrDvs[MAXN * MAXN + 1];
int tab[MAXN * MAXN];

bool TabComp(int a, int b)
{
	if (nPrDvs[a] == nPrDvs[b])
	{
		return a < b;
	}
	return nPrDvs[a] < nPrDvs[b];
}

void FillNPrDvs()
{
	for (int i = 2; i <= n * n; i++)
	{
		nPrDvs[i] = 0;
	}

	for (int i = 2; i <= n * n; i++)
	{
		if (nPrDvs[i] == 0)
		{
			for (int j = i * 2; j <= n * n; j += i)
			{
				nPrDvs[j]++;
			}
			nPrDvs[i] = 1;
		}
	}
}

void InitTab()
{
	for (int i = 1; i <= n * n; i++)
	{
		tab[i - 1] = i;
	}
}

int main()
{
	cin >> n;
	FillNPrDvs();
	InitTab();
	sort(tab + 1, tab + n * n, TabComp);

	int r, c;
	cin >> r >> c; r--; c--;

	cout << tab[r * n + c] << endl;

	return 0;
}
