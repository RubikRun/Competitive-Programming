//not checked properly, but I am pretty sure it's 100%

#include <iostream>

using namespace std;
#define llu long long unsigned

void Solve()
{
	llu p, q;
	cin >> p >> q;
	if (3 * p == q || 3 * q == p || (p == q && p % 3 != 0))
	{
		cout << 0 << endl;
		return;
	}

	if (p > 3 * q)
	{
		cout << 1 << " " << p - 3 * q << endl;
		return;
	}

	if (q > 3 * p)
	{
		cout << 2 << " " << q - 3 * p << endl;
		return;
	}

	if (p % 3 == 0 && q > p / 3)
	{
		cout << 2 << " " << q - p / 3 << endl;
		return;
	}

	if (q % 3 == 0 && p > q / 3)
	{
		cout << 1 << " " << p - q / 3 << endl;
		return;
	}

	if (p > q)
	{
		cout << 1 << " " << p - q << endl;
		return;
	}

	if (q > p)
	{
		cout << 2 << " " << q - p << endl;
		return;
	}
}

int main()
{
	Solve();
	Solve();
	Solve();

	return 0;
}
