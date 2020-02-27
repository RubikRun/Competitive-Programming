//checked - 100%

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

#define MaxNumberOfDigits 52

struct Number
{
    int digits[MaxNumberOfDigits];
    int numberOfDigits;
};

Number NumberFromInt(int value)
{
    Number number;
    number.numberOfDigits = 0;


    do
    {
        number.digits[number.numberOfDigits++] = value % 10;
        value /= 10;
    }
    while (value != 0);

    for (int i = number.numberOfDigits; i < MaxNumberOfDigits; i++)
    {
        number.digits[i] = 0;
    }

    return number;
}

Number NumberFromString(char s[])
{
    Number number;

    number.numberOfDigits = strlen(s);
    for (int i = 0; i < number.numberOfDigits; i++)
    {
        number.digits[i] = s[number.numberOfDigits - 1 - i] - '0';
    }
    for (int i = number.numberOfDigits; i < MaxNumberOfDigits; i++)
    {
        number.digits[i] = 0;
    }

    return number;
}

Number ReadNumber()
{
    char numberString[MaxNumberOfDigits];
    scanf("%s", numberString);

    Number number = NumberFromString(numberString);

    return number;
}

Number NumberFromDigits(int givenDigits[], int givenNumberOfDigits)
{
    Number number;
    number.numberOfDigits = givenNumberOfDigits;

    for (int i = 0; i < number.numberOfDigits; i++)
    {
        number.digits[i] = givenDigits[i];
    }
    for (int i = number.numberOfDigits; i < MaxNumberOfDigits; i++)
    {
        number.digits[i] = 0;
    }

    return number;
}

Number SmallestNumberFromDigits(int givenDigits[], int givenNumberOfDigits)
{
    sort(givenDigits, givenDigits + givenNumberOfDigits, greater<int>());

    for (int numberOfZeros = givenNumberOfDigits - 1; numberOfZeros >= 0; numberOfZeros--)
    {
        if (givenDigits[numberOfZeros] != 0)
        {
            int t = givenDigits[numberOfZeros];
            givenDigits[numberOfZeros] = 0;
            givenDigits[givenNumberOfDigits - 1] = t;

            break;
        }
    }

    return NumberFromDigits(givenDigits, givenNumberOfDigits);
}

Number GreatestNumberFromDigits(int givenDigits[], int givenNumberOfDigits)
{
    sort(givenDigits, givenDigits + givenNumberOfDigits);

    return NumberFromDigits(givenDigits, givenNumberOfDigits);
}

Number Sum(Number number1, Number number2)
{
    Number answer;
    int carry = 0;

    int i = 0;
    while (carry != 0 || i < number1.numberOfDigits || i < number2.numberOfDigits)
    {
        answer.digits[i] = number1.digits[i] + number2.digits[i] + carry;
        carry = answer.digits[i] / 10;
        answer.digits[i] %= 10;

        i++;
    }

    answer.numberOfDigits = i;

    return answer;
}

void PrintNumber(Number number)
{
    for (int i = number.numberOfDigits - 1; i >= 0; i--)
    {
        printf("%d", number.digits[i]);
    }
    printf("\n");
}


int main()
{
    Number number = ReadNumber();
    Number smallestNumber = SmallestNumberFromDigits(number.digits, number.numberOfDigits);
    Number greatestNumber = GreatestNumberFromDigits(number.digits, number.numberOfDigits);
    PrintNumber(Sum(smallestNumber, greatestNumber));
}