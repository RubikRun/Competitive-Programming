//fuck it

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MaxNumberOfDigits 100

struct Number
{
    int numberOfDigits;
    int digits[MaxNumberOfDigits];
};

Number p;

Number Add(Number& a, Number& b);
Number Modulo(Number& a, Number& b);

void PutLeadingZeros(Number& number)
{
    for (int i = number.numberOfDigits; i < MaxNumberOfDigits; i++)
    {
        number.digits[i] = 0;
    }
}

Number GetNumber(int decimal)
{
    if (decimal == 0)
    {
        Number result;
        result.numberOfDigits = 1;
        result.digits[0] = 0;
        PutLeadingZeros(result);
        return result;
    }
    Number result;

    int i = 0;
    while (decimal != 0)
    {
        result.digits[i] = decimal % 10;
        decimal /= 10;

        i++;
    }

    result.numberOfDigits = i;
    PutLeadingZeros(result);

    return result;
}

int GetInt(Number& number)
{
    int decimal = 0;

    for (int i = number.numberOfDigits - 1; i >= 0; i--)
    {
        decimal *= 10;
        decimal += number.digits[i];
    }

    return decimal;
}

Number ReadNumber()
{
    Number result;

    char input[MaxNumberOfDigits + 1];
    scanf("%s", input);

    result.numberOfDigits = (int)strlen(input);
    for (int i = 0; i < result.numberOfDigits; i++)
    {
        result.digits[i] = input[result.numberOfDigits - 1 - i] - '0';
    }

    PutLeadingZeros(result);

    return result;
}

void PrintNumber(Number& number)
{
    for (int i = number.numberOfDigits - 1; i >= 0; i--)
    {
        printf("%d", number.digits[i]);
    }

    printf("\n");
}

Number MultiplyByDigit(Number& number, int digit)
{
    Number result;

    int i = 0;
    int carry = 0;

    while (i < number.numberOfDigits || carry != 0)
    {
        result.digits[i] = number.digits[i] * digit + carry;
        carry = result.digits[i] / 10;
        result.digits[i] %= 10;

        i++;
    }

    result.numberOfDigits = i;
    while (result.digits[result.numberOfDigits - 1] == 0 && result.numberOfDigits > 1)
    {
        result.numberOfDigits--;
    }

    PutLeadingZeros(result);

    return result;
}

Number Multiply(Number& a, Number& b)
{
    int matrix[MaxNumberOfDigits][MaxNumberOfDigits * 2];


    int lastCol = -1;
    for (int row = 0; row < b.numberOfDigits; row++)
    {
        Number currentNumber = MultiplyByDigit(a, b.digits[row]);

        for (int col = 0; col < MaxNumberOfDigits * 2; col++)
        {
            if (col < row || col >= currentNumber.numberOfDigits + row)
            {
                matrix[row][col] = 0;
            }
            else
            {
                matrix[row][col] = currentNumber.digits[col - row];
            }
        }

        if (!(currentNumber.numberOfDigits == 1 && currentNumber.digits[0] == 0))
        {
            lastCol = max(lastCol, currentNumber.numberOfDigits + row - 1);
        }
    }

    Number result;

    int col = 0, carry = 0, sum;
    do
    {
        sum = carry;
        for (int row = 0; row < b.numberOfDigits; row++)
        {
            sum += matrix[row][col];
        }

        result.digits[col] = sum % 10;
        carry = sum / 10;

        col++;
    } while (col <= lastCol || carry != 0);

    result.numberOfDigits = col;

    PutLeadingZeros(result);

    return result;
}

bool Equals(Number& a, Number& b)
{
    if (a.numberOfDigits != b.numberOfDigits)
    {
        return false;
    }

    for (int i = 0; i < a.numberOfDigits; i++)
    {
        if (a.digits[i] != b.digits[i])
        {
            return false;
        }
    }

    return true;
}

Number DivideByTwo(Number& number)
{
    Number result;

    int carry = 0;
    for (int i = number.numberOfDigits - 1; i >= 0; i--)
    {
        result.digits[i] = (number.digits[i] + carry * 10) / 2;
        carry = number.digits[i] % 2;
    }

    result.numberOfDigits = number.numberOfDigits;
    if (result.digits[result.numberOfDigits - 1] == 0)
    {
        result.numberOfDigits--;
    }

    return result;
}

Number Subtract(Number& a, Number& b)
{
    Number result;
    Number zero = GetNumber(0);
    Number h1, h2;

    Number carry = zero;
    int i = 0;

    while (i < a.numberOfDigits || i < b.numberOfDigits || !Equals(carry, zero))
    {
        h2 = GetNumber()
        result.digits[i] = a.digits[i] - b.digits[i] - carry;

        carry = 0;
        while (result.digits[i] < 0)
        {
            result.digits[i] = Add(result.digits[i], p);
            carry++;
        }

        i++;
    }

    result.numberOfDigits = i;

    while (result.digits[result.numberOfDigits - 1] == 0 && result.numberOfDigits > 1)
    {
        result.numberOfDigits--;
    }

    PutLeadingZeros(result);

    return result;
}

bool Smaller(Number& a, Number& b)
{
    if (a.numberOfDigits != b.numberOfDigits)
    {
        return a.numberOfDigits < b.numberOfDigits;
    }

    for (int i = a.numberOfDigits - 1; i >= 0; i--)
    {
        if (a.digits[i] < b.digits[i])
        {
            return true;
        }
        else if (a.digits[i] > b.digits[i])
        {
            return false;
        }
    }

    return false;
}

bool SmallerOrEqual(Number& a, Number& b)
{
    if (a.numberOfDigits != b.numberOfDigits)
    {
        return a.numberOfDigits < b.numberOfDigits;
    }

    for (int i = a.numberOfDigits - 1; i >= 0; i--)
    {
        if (a.digits[i] < b.digits[i])
        {
            return true;
        }
        else if (a.digits[i] > b.digits[i])
        {
            return false;
        }
    }

    return true;
}

bool Greater(Number& a, Number& b)
{
    if (a.numberOfDigits != b.numberOfDigits)
    {
        return a.numberOfDigits > b.numberOfDigits;
    }

    for (int i = a.numberOfDigits - 1; i >= 0; i--)
    {
        if (a.digits[i] > b.digits[i])
        {
            return true;
        }
        else if (a.digits[i] < b.digits[i])
        {
            return false;
        }
    }

    return false;
}

Number Divide(Number& a, Number& b)
{
    if (Greater(b, a))
    {
        Number result = GetNumber(0);
        return result;
    }

    Number one = GetNumber(1);

    if (Equals(b, one))
    {
        return a;
    }

    Number result;

    Number first = GetNumber(0), last = a;

    Number h1, h2, h3;
    do
    {
        h1 = Add(first, last);
        result = DivideByTwo(h1);

        h1 = Multiply(result, b);
        if (SmallerOrEqual(h1, a))
        {
            first = result;
        }
        else
        {
            last = result;
        }

        h2 = Add(result, one);
        h3 = Multiply(h2, b);
    } while (!(SmallerOrEqual(h1, a) && Greater(h3, a)));

    return result;
}

Number Add(Number& a, Number& b)
{
    Number result;
    Number zero = GetNumber(0);
    Number h1, h2;

    Number carry = zero;
    int i = 0;

    while (i < a.numberOfDigits || i < b.numberOfDigits || !Equals(carry, zero))
    {
        h2 = GetNumber(a.digits[i] + b.digits[i]);
        h2 = Add(h2, carry);
        result.digits[i] = GetInt(h2);
        h1 = GetNumber(result.digits[i]);
        carry = Divide(h1, p);
        h2 = Modulo(h1, p);
        result.digits[i] = GetInt(h2);

        i++;
    }

    result.numberOfDigits = i;
    PutLeadingZeros(result);

    return result;
}

Number Modulo(Number& a, Number& b)
{
    Number x = Divide(a, b);

    Number h1 = Multiply(b, x);
    Number result = Subtract(a, h1);

    return result;
}



int main()
{
    p = ReadNumber();

    Number one = GetNumber(1);
    Number pSquared = Multiply(p, p);
    Number h1;

    Number stepsNeeded;
    stepsNeeded = ReadNumber();
    stepsNeeded = Subtract(stepsNeeded, one);

    Number apple, banana;
    apple = ReadNumber();
    banana = ReadNumber();
    apple = Modulo(apple, pSquared);
    banana = Modulo(banana, pSquared);
    Number beginApple = apple, beginBanana = banana;
    h1 = Add(apple, banana);
    Number cucumber = Modulo(h1, pSquared);

    Number stepsTaken = GetNumber(0);
    while (Smaller(stepsTaken, stepsNeeded))
    {
        apple = banana;
        banana = cucumber;
        h1 = Add(apple, banana);
        cucumber = Modulo(h1, pSquared);

        if (Equals(apple, beginApple) && Equals(banana, beginBanana))
        {
            Number cycle = stepsTaken;
            stepsNeeded = Modulo(stepsNeeded, cycle);
            stepsTaken = GetNumber(0);

            while (Smaller(stepsTaken, stepsNeeded))
            {
                apple = banana;
                banana = cucumber;
                h1 = Add(apple, banana);
                cucumber = Modulo(h1, pSquared);

                stepsTaken = Add(stepsTaken, one);
            }

            h1 = Divide(apple, p);
            Number answer = Modulo(h1, p);
            PrintNumber(answer);

            return 0;
        }

        stepsTaken = Add(stepsTaken, one);
    }

    h1 = Divide(apple, p);
    Number answer = Modulo(h1, p);
    PrintNumber(answer);

    return 0;
}