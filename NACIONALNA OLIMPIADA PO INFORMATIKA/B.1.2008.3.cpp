#include <cstdio>
using namespace std;

void Solve(int numberOfMen, int numberOfWomen)
{
    if (numberOfWomen > 2 * ((numberOfMen) / 2))
    {
        printf("NO\n");
        return;
    }

    while (numberOfMen > 0 || numberOfWomen > 0)
    {
        if (numberOfWomen > 0)
        {
            printf("0");
            numberOfWomen--;
        }
        if (numberOfWomen > 0)
        {
            printf("0");
            numberOfWomen--;
        }
        if (numberOfMen > 0)
        {
            printf("1");
            numberOfMen--;
        }
        if (numberOfMen > 0)
        {
            printf("1");
            numberOfMen--;
        }
    }
    printf("\n");
}

int main() {
    int numberOfMen, numberOfWomen;

    scanf("%d%d", &numberOfMen, &numberOfWomen);
    Solve(numberOfMen, numberOfWomen);
    scanf("%d%d", &numberOfMen, &numberOfWomen);
    Solve(numberOfMen, numberOfWomen);
}