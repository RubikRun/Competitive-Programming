//checked - 100%

#include <cstdio>

using namespace std;
#define MaxWidth 102
#define MaxLength 102
#define MaxHeight 102
#define MaxNumberOfAnswers 500000

int tab[MaxWidth][MaxLength][MaxHeight];
int width;
int length;
int height;

int sumTab[MaxWidth][MaxLength][MaxHeight];

void ReadTab()
{
    scanf("%d %d %d", &width, &length, &height);

    for (int k = 0; k < height; k++)
    {
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                scanf("%d", &tab[i][j][k]);
            }
        }
    }
}

int GetSumTab(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0)
    {
        return 0;
    }
    return sumTab[x][y][z];
}

void FillSumTab()
{
    for (int k = 0; k < height; k++)
    {
        for (int j = 0; j < length; j++)
        {
            for (int i = 0; i < width; i++)
            {
                sumTab[i][j][k] = tab[i][j][k]
                + GetSumTab(i - 1, j, k) + GetSumTab(i, j - 1, k) + GetSumTab(i, j, k - 1)
                - GetSumTab(i, j - 1, k - 1) - GetSumTab(i - 1, j, k - 1) - GetSumTab(i - 1, j - 1, k)
                + GetSumTab(i - 1, j - 1, k - 1);
            }
        }
    }
}

int GetRegionSum(int x1, int y1, int z1, int x2, int y2, int z2)
{
    return GetSumTab(x2, y2, z2)
    - GetSumTab(x1 - 1, y2, z2) - GetSumTab(x2, y1 - 1, z2) - GetSumTab(x2, y2, z1 - 1)
    + GetSumTab(x2, y1 - 1, z1 - 1) + GetSumTab(x1 - 1, y2, z1 - 1) + GetSumTab(x1 - 1, y1 - 1, z2)
    - GetSumTab(x1 - 1, y1 - 1, z1 - 1);
}

int main()
{
    ReadTab();
    FillSumTab();

    int answers[MaxNumberOfAnswers];
    int numberOfAnswers = 0;

    int x1, y1, z1, x2, y2, z2;
    while (scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2) != -1)
    {
        x2--; y2--; z2--;
        answers[numberOfAnswers++] = GetRegionSum(x1, y1, z1, x2, y2, z2);
    }

    for (int i = 0; i < numberOfAnswers; i++)
    {
        printf("%d\n", answers[i]);
    }

    return 0;
}
