#include <cstdio>
using namespace std;

unsigned ClosestPowerOfTwo(unsigned n) //Finds the closest power of 2 which is less or equal to n
{
    unsigned power = 0;

    for (unsigned i = 0; i < 32 && n != 0; i++)
    {
        if (n % 2 == 1)
        {
            power = i;
        }
        n = n >> 1;
    }

    return 1 << power;
}

unsigned Log2(unsigned n) //Calculates Log2(n) with n being a power of 2
{
    for (unsigned i = 0; i < 32 && n != 0; i++)
    {
        if (n % 2 == 1)
        {
            return i;
        }
        n = n >> 1;
    }
}

int S(int n)
{
    if (n == 0)
    {
        return 0;
    }

    int closestPowerOfTwo = ClosestPowerOfTwo(n);
    int power = Log2(closestPowerOfTwo);

    return power * closestPowerOfTwo / 2 + n - closestPowerOfTwo + 1 + S(n % closestPowerOfTwo);
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", S(n));
    return 0;
}