#include <iostream>
#include <algorithm>

using namespace std;

int n, m, k;
int b[100000], d[100000];

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> b[i];
	}
	for (int i = 0; i < n - 1; i++)
	{
		d[i] = b[i + 1] - b[i] - 1;
	}
	sort(d, d + n - 1);
	int r = n;
	for (int i = 0; i < n - k; i++)
	{
		r += d[i];
	}
	cout << r << endl;
	return 0;
}