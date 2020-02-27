//checked - 100%

#include <cstdio>
using namespace std;

int Apples(int price)
{
    if (price == 1)
    {
        return 1;
    }

    if (price == 2)
    {
        return 2;
    }

    if (price % 3 == 0)
    {
        return 3 * Apples(price / 3) + 1;
    }

    if (price % 3 == 1)
    {
        return Apples(price - 1) + 1;
    }

    if (price % 3 == 2)
    {
        return Apples(price - 2) + 2;
    }
}

int main()
{
    int price;
    scanf("%d", &price);

    int apples = Apples(price);
    printf("%d\n", apples);

    return 0;
}
