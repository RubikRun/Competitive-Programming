//checked - 100%

#include <cstdio>
using namespace std;

long long unsigned GetFirstCyclicIndex(int unit)
{
    int a = 0, b = 0, c = 1, d = 1;
    long long unsigned firstCyclicIndex = 0;

    do
    {
        a = b;
        b = c;
        c = d;
        d = (a + b + c) % unit;
        firstCyclicIndex++;
    } while (a != 0 || b != 0 || c != 1);

    return firstCyclicIndex;
}

int main()
{
    int unit;
    scanf("%d", &unit);

    long long unsigned firstCyclicIndex = GetFirstCyclicIndex(unit);
    printf("%llu\n", firstCyclicIndex);

    return 0;
}