//checked - 100%

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
#define Number vector<int>

Number ReadNumber() //works
{
    string digits;
    cin >> digits;

    Number number;
    for (int i = digits.size() - 1; i >= 0; i--)
    {
        number.push_back(digits[i] - '0');
    }

    return number;
}

Number GetNumberFromInt(int x) //works
{
    if (x == 0)
    {
        return {0};
    }
    Number number;

    while (x != 0)
    {
        number.push_back(x % 10);
        x /= 10;
    }

    return number;
}

Number CopyNumber(Number oldNumber) //works
{
    Number newNumber;

    for (int i = 0; i < oldNumber.size(); i++)
    {
        newNumber.push_back(oldNumber[i]);
    }

    return newNumber;
}

int CompareNumbers(Number a, Number b) //works
{
    if (a.size() < b.size())
    {
        return -1;
    }
    if (a.size() > b.size())
    {
        return 1;
    }

    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (a[i] < b[i])
        {
            return -1;
        }
        if (a[i] > b[i])
        {
            return 1;
        }
    }

    return 0;
}

Number GetSum(Number a, Number b) //works
{
    Number sum;

    int carry = 0;
    for (int i = 0; i < a.size() || i < b.size() || carry != 0; i++)
    {
        int aDigit = 0;
        if (i < a.size())
        {
            aDigit = a[i];
        }

        int bDigit = 0;
        if (i < b.size())
        {
            bDigit = b[i];
        }

        sum.push_back(aDigit + bDigit + carry);
        carry = sum.back() / 10;
        sum.back() %= 10;
    }

    return sum;
}

Number DivideByTwo(Number x) //works
{
    Number result;

    int carry = 0;
    for (int i = x.size() - 1; i >= 0; i--)
    {
        int curr = carry * 10 + x[i];
        if (!result.empty() || curr / 2 != 0)
        {
            result.push_back(curr / 2);
        }
        carry = curr % 2;
    }

    if (result.empty())
    {
        return {0};
    }

    reverse(result.begin(), result.end());

    return result;
}

Number GetDigitProduct(Number a, int b) //works
{
    Number product;

    int carry = 0;
    for (int i = 0; i < a.size(); i++)
    {
        product.push_back(a[i] * b + carry);
        carry = product.back() / 10;
        product.back() %= 10;
    }
    if (carry != 0)
    {
        product.push_back(carry);
    }

    return product;
}

Number MultiplyByPowerOfTen(Number a, int power) //works
{
    Number result;

    for (int i = 0; i < power; i++)
    {
        result.push_back(0);
    }
    for (int i = 0; i < a.size(); i++)
    {
        result.push_back(a[i]);
    }

    return result;
}

Number GetProduct(Number a, Number b) //works
{
    if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0))
    {
        return {0};
    }
    Number product = GetDigitProduct(a, b[0]);

    for (int i = 1; i < b.size(); i++)
    {
        product = GetSum(product, MultiplyByPowerOfTen(GetDigitProduct(a, b[i]), i));
    }

    return product;
}

Number Subtract(Number a, Number b) //works
{
    if (CompareNumbers(a, b) <= 0)
    {
        return {0};
    }

    Number result;

    int carry = 0;
    for (int i = 0; i < a.size(); i++)
    {
        int bDigit = 0;
        if (i < b.size())
        {
            bDigit = b[i];
        }

        result.push_back(a[i] - bDigit - carry);
        carry = 0;
        if (result.back() < 0)
        {
            result.back() += 10;
            carry++;
        }
    }

    while (result.back() == 0)
    {
        result.pop_back();
    }

    return result;
}

void PrintNumber(Number x) //works
{
    for (int i = x.size() - 1; i >= 0; i--)
    {
        cout << x[i];
    }
    cout << endl;
}

int main()
{
    Number m, n;
    m = ReadNumber();
    n = ReadNumber();

    Number first, mid, last;

    first = GetNumberFromInt(1);
    last = CopyNumber(m);
    while (CompareNumbers(first, last) <= 0)
    {
        mid = DivideByTwo(GetSum(first, last));

        if (CompareNumbers(GetProduct(mid, GetSum(mid, GetNumberFromInt(1))), m) >= 0 && CompareNumbers(GetProduct(mid, Subtract(mid, GetNumberFromInt(1))), m) < 0)
        {
            break;
        }
        if (CompareNumbers(GetProduct(mid, GetSum(mid, GetNumberFromInt(1))), m) < 0)
        {
            first = GetSum(mid, GetNumberFromInt(1));
        }
        else
        {
            last = Subtract(mid, GetNumberFromInt(1));
        }
    }
    Number p = CopyNumber(mid);

    first = GetNumberFromInt(1);
    last = CopyNumber(n);
    while (CompareNumbers(first, last) <= 0)
    {
        mid = DivideByTwo(GetSum(first, last));

        if (CompareNumbers(GetProduct(mid, GetSum(mid, GetNumberFromInt(1))), n) <= 0 && CompareNumbers(GetProduct(GetSum(mid, GetNumberFromInt(1)), GetSum(mid, GetNumberFromInt(2))), n) > 0)
        {
            break;
        }
        if (CompareNumbers(GetProduct(mid, GetSum(mid, GetNumberFromInt(1))), n) > 0)
        {
            last = Subtract(mid, GetNumberFromInt(1));
        }
        else
        {
            first = GetSum(mid, GetNumberFromInt(1));
        }
    }
    Number q = CopyNumber(mid);

    if (CompareNumbers(p, q) > 0)
    {
        cout << 0 << endl;
        return 0;
    }

    PrintNumber(GetSum(Subtract(q, p), GetNumberFromInt(1)));

    return 0;
}
