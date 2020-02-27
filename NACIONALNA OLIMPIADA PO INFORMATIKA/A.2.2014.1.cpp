//checked - 100%

#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 100000
#define MaxSalary 100000
#define MinSalary 300

int salaries[MAXN];
int children[MAXN];
int n;

void FindChildren()
{
	children[n - 1] = -1;

	for (int i = n - 2; i >= 0; i--)
	{
		children[i] = -1;
		for (int j = i + 1; j != -1; j = children[j])
		{
			if (salaries[j] > salaries[i])
			{
				children[i] = j;
				break;
			}
		}
	}
}

bool UpdateSalaries()
{
	FindChildren();

	bool nothingNew = true;
	int newSalaries[MAXN];
	for (int i = 0; i < n; i++)
	{
		if (children[i] != -1)
		{
			newSalaries[i] = (salaries[i] + salaries[children[i]]) / 2;
			nothingNew = false;
		}
		else
		{
			newSalaries[i] = salaries[i];
		}
	}
	if (nothingNew)
	{
		return false;
	}

	vector<int> groups[MaxSalary + 1];
	vector<int> newGroups[MaxSalary + 1];
	for (int i = 0; i < n; i++)
	{
		groups[salaries[i]].push_back(i);
		newGroups[newSalaries[i]].push_back(i);
	}

	bool order = true;
	int j = MinSalary;
	for (int i = MinSalary; i <= MaxSalary; i++)
	{
		if (!groups[i].empty())
		{
			while (newGroups[j].empty())
			{
				if (j == MaxSalary)
				{
					order = false;
					break;
				}
				j++;
			}
			if (groups[i].size() != newGroups[j].size())
			{
				order = false;
				break;
			}
			for (int k = 0; k < groups[i].size(); k++)
			{
				if (groups[i][k] != newGroups[j][k])
				{
					order = false;
					break;
				}
			}
			j++;
		}
	}

	if (order)
	{
		for (int i = 0; i < n; i++)
		{
			salaries[i] = newSalaries[i];
		}
		return true;
	}
	else
	{
		return false;
	}
}

void PrintSalaries()
{
        for (int i = 0; i < n; i++)
        {
                printf("%d\n", salaries[i]);
        }
}

void FindFinalSalaries()
{
	for (int i = 0; i < 12; i++)
	{
		if (!UpdateSalaries())
		{
			return;
		}
	}
}

void ReadSalaries()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &salaries[i]);
	}
}

int main()
{
	ReadSalaries();
	FindFinalSalaries();
	PrintSalaries();

	return 0;
}
