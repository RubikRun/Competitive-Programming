#include <cstdio>
using namespace std;

#define MaxPossibleDenominator 100

long long unsigned GCD(long long unsigned a, long long unsigned b)
{
    long long unsigned t;
    while (b != 0)
    {
        t = a;
        a = b;
        b = t % b;
    }

    return a;
}

struct Fraction
{
    long long unsigned numerator;
    long long unsigned denominator;
};

Fraction SumOfIrreducableFractions(long long unsigned minComponent, long long unsigned maxComponent)
{
    Fraction finalFraction;

    finalFraction.denominator = 1;
    for (long long unsigned eachDenominator = minComponent + 1; eachDenominator <= maxComponent; eachDenominator++)
    {
        finalFraction.denominator *= eachDenominator;
    }

    finalFraction.numerator = 0;
    long long unsigned currentNumerator;
    for (long long unsigned eachDenominator = minComponent + 1; eachDenominator <= maxComponent; eachDenominator++)
    {
        currentNumerator = 0;
        for (long long unsigned potentialAddend = minComponent; potentialAddend < eachDenominator; potentialAddend++)
        {
            if (GCD(potentialAddend, eachDenominator))
            {
                currentNumerator += potentialAddend;
            }
        }

        currentNumerator *= finalFraction.denominator / eachDenominator;
        finalFraction.numerator += currentNumerator;
    }

    return finalFraction;
}

void MakeFractionIrreducable(Fraction& fraction)
{
    long long unsigned gcd = GCD(fraction.numerator, fraction.denominator);
    fraction.numerator /= gcd;
    fraction.denominator /= gcd;
}

void PrintFraction(Fraction& fraction)
{
    printf("%llu/%llu\n", fraction.numerator, fraction.denominator);
}

int main()
{
    long long unsigned minComponent, maxComponent;
    scanf("%llu%llu", &minComponent, &maxComponent);

    Fraction wantedSum = SumOfIrreducableFractions(minComponent, maxComponent);
    MakeFractionIrreducable(wantedSum);

    PrintFraction(wantedSum);

    return 0;
}