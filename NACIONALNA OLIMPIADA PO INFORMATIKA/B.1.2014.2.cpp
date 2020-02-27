//checked - 100%

#include <cstdio>
#include <cstring>

using namespace std;

#define NumberOfAllPossibleValues 40001

int NumberFromString(char s[], int sl)
{
    int number = 0;
    for (int i = 0; i < sl; i++)
    {
        number *= 10;
        number += s[i] - '0';
    }

    return number;
}

int ReadTaxAndGetNumber()
{
    char taxDigits[10];
    scanf("%s", taxDigits);
    int sl = strlen(taxDigits);

    taxDigits[sl-3] = taxDigits[sl-2];
    taxDigits[sl-2] = taxDigits[sl-1];
    sl--;

    return NumberFromString(taxDigits, sl);
}

int main()
{
    int numberOfAllTaxes, numberOfPaidTaxes;
    scanf("%d%d", &numberOfAllTaxes, &numberOfPaidTaxes);

    int numbersOfUnpaidTaxes[NumberOfAllPossibleValues];
    for (int taxValue = 0; taxValue < NumberOfAllPossibleValues; taxValue++)
    {
        numbersOfUnpaidTaxes[taxValue] = 0;
    }
    for (int taxIndex = 0; taxIndex < numberOfAllTaxes; taxIndex++)
    {
        numbersOfUnpaidTaxes[ReadTaxAndGetNumber()]++;
    }
    for (int taxIndex = 0; taxIndex < numberOfPaidTaxes; taxIndex++)
    {
        numbersOfUnpaidTaxes[ReadTaxAndGetNumber()]--;
    }

    int lastTaxForPrinting = -1;
    for (int taxValue = NumberOfAllPossibleValues - 1; taxValue >= 0; taxValue--)
    {
        for (int times = 0; times < numbersOfUnpaidTaxes[taxValue]; times++)
        {
            if (lastTaxForPrinting != -1)
            {
                printf("%d.%.2d ", lastTaxForPrinting / 100, lastTaxForPrinting % 100);
            }
            lastTaxForPrinting = taxValue;
        }
    }
    if (lastTaxForPrinting != -1)
    {
        printf("%d.%.2d\n", lastTaxForPrinting / 100, lastTaxForPrinting % 100);
    }

    return 0;
}