//checked - 100%

#include <iostream>
#include <algorithm>

using namespace std;
#define MaxNumberOfVariables 19
#define MaxNumberOfProducts 9998

struct Product
{
    int coef;
    int powers[MaxNumberOfVariables];
};

struct Polynomial
{
    int numberOfVariables;
    Product products[MaxNumberOfProducts];
    int numberOfProducts;
};

Polynomial ReadPolynomial()
{
    Polynomial polynomial;

    scanf("%d %d", &polynomial.numberOfVariables, &polynomial.numberOfProducts);

    int numberOfDistinctProducts = 0;
    for (int i = 0; i < polynomial.numberOfProducts; i++)
    {
        scanf("%d", &polynomial.products[numberOfDistinctProducts].coef);
        for (int j = 0; j < polynomial.numberOfVariables; j++)
        {
            scanf("%d", &polynomial.products[numberOfDistinctProducts].powers[j]);
        }

        bool productIsNew = true;
        for (int j = 0; j < numberOfDistinctProducts; j++)
        {
            bool samePowers = true;
            for (int k = 0; k < polynomial.numberOfVariables; k++)
            {
                if (polynomial.products[numberOfDistinctProducts].powers[k] != polynomial.products[j].powers[k])
                {
                    samePowers = false;
                    break;
                }
            }

            if (samePowers)
            {
                productIsNew = false;
                polynomial.products[j].coef += polynomial.products[numberOfDistinctProducts].coef;
                break;
            }
        }

        if (productIsNew)
        {
            numberOfDistinctProducts++;
        }
    }
    polynomial.numberOfProducts = numberOfDistinctProducts;

    return polynomial;
}

bool PolynomialIsSymmetric(Polynomial& polynomial)
{
    bool checked[MaxNumberOfProducts];
    for (int i = 0; i < polynomial.numberOfProducts; i++)
    {
        checked[i] = false;
    }

    for (int i = 0; i < polynomial.numberOfProducts; i++)
    {
        if (checked[i])
        {
            continue;
        }

        int currPowers[MaxNumberOfVariables];
        for (int j = 0; j < polynomial.numberOfVariables; j++)
        {
            currPowers[j] = polynomial.products[i].powers[j];
        }

        sort(currPowers, currPowers + polynomial.numberOfVariables);

        do
        {
            bool found = false;
            for (int j = i; j < polynomial.numberOfProducts; j++)
            {
                if (polynomial.products[j].coef != polynomial.products[i].coef)
                {
                    continue;
                }

                bool samePowers = true;
                for (int k = 0; k < polynomial.numberOfVariables; k++)
                {
                    if (polynomial.products[j].powers[k] != currPowers[k])
                    {
                        samePowers = false;
                        break;
                    }
                }

                if (samePowers)
                {
                    found = true;
                    checked[j] = true;
                    break;
                }
            }

            if (!found)
            {
                return false;
            }
        } while(next_permutation(currPowers, currPowers + polynomial.numberOfVariables));
    }

    return true;
}

int main()
{
    int numberOfPolynomials;
    scanf("%d", &numberOfPolynomials);

    for (int i = 0; i < numberOfPolynomials; i++)
    {
        Polynomial polynomial = ReadPolynomial();
        if (PolynomialIsSymmetric(polynomial))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }

    printf("\n");

    return 0;
}
