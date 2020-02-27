//checked - 100%

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> numbers;

#define MAXN 12

int GetDigit(int begin, int end, char givenBits[])
{
    int digit = 0;

    for (int bitIndex = begin; bitIndex < end; bitIndex++)
    {
        digit *= 2;
        digit += givenBits[bitIndex] - '0';
    }

    return digit - 3;
}

int GetNumberFromDigits(int digits[], int numberOfDigits)
{
    int number = 0;

    for (int digitIndex = 0; digitIndex < numberOfDigits; digitIndex++)
    {
        number *= 10;
        number += digits[digitIndex];
    }

    return number;
}

void AddToNumbers(int digitsBegins[], int numberOfDigits , char givenBits[], int givenBitsLen)
{
    int digits[MAXN];

    for (int i=0; i<numberOfDigits; i++)
    {
        if (i < numberOfDigits-1) digits[i]=GetDigit(digitsBegins[i], digitsBegins[i+1], givenBits);
        else digits[i]=GetDigit(digitsBegins[i], givenBitsLen, givenBits);

        if (digits[i] < 0 || digits[i] > 9)
        {
            return;
        }
    }
    if (digits[0] == 0 && numberOfDigits > 1)
    {
        return;
    }

    numbers.push_back(GetNumberFromDigits(digits, numberOfDigits));
}

void DigTree(int digitIndex, int digitsBegins[], int numberOfDigits, char givenBits[], int givenBitsLen)
{
    if (digitIndex == 0)
    {
        digitsBegins[digitIndex] = 0;
        DigTree(digitIndex+1, digitsBegins, numberOfDigits, givenBits, givenBitsLen);
    }
    else if (digitIndex == numberOfDigits)
    {
        if (givenBitsLen - digitsBegins[digitIndex-1] <= 4)
        {
            AddToNumbers(digitsBegins, numberOfDigits, givenBits, givenBitsLen);
        }
    }
    else
    {
        for (int currentDigitLenInBits = 1; currentDigitLenInBits <= 4; currentDigitLenInBits++)
        {
            if (givenBits[digitsBegins[digitIndex-1]+currentDigitLenInBits] =='1')
            {
                digitsBegins[digitIndex] = digitsBegins[digitIndex-1] + currentDigitLenInBits;
                DigTree(digitIndex+1, digitsBegins, numberOfDigits, givenBits, givenBitsLen);
            }
        }
    }
}

void FindAllNumbers(char givenBits[], int givenBitsLen)
{
    int minNumberOfDigits = (givenBitsLen + 3) / 4;
    int maxNumberOfDigits = 0;
    for (int bitIndex = 0; bitIndex < givenBitsLen; bitIndex++) maxNumberOfDigits += givenBits[bitIndex]-'0';

    int digitsBegins[MAXN];
    for (int numberOfDigits = minNumberOfDigits; numberOfDigits <= maxNumberOfDigits; numberOfDigits++)
    {
        DigTree(0, digitsBegins, numberOfDigits, givenBits, givenBitsLen);
    }
}

int main()
{
    char givenBits[MAXN];
    scanf("%s", givenBits);
    int givenBitsLen = strlen(givenBits);

    FindAllNumbers(givenBits, givenBitsLen);
    sort(numbers.begin(), numbers.end());

    for (int numberIndex=0; numberIndex<numbers.size(); numberIndex++)
    {
        printf("%d\n", numbers[numberIndex]);
    }
    if (numbers.size()==0)
    {
        printf("-1\n");
    }

    return 0;
}
