/*
ID: borisd22
TASK: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("pprime.out");
ifstream fin ("pprime.in");

bool IsPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    if (n == 2)
    {
        return true;
    }
    if (n % 2 == 0)
    {
        return false;
    }

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int FirstDigit(int n)
{
    while (n >= 10)
    {
        n /= 10;
    }

    return n;
}

int GetPalindrome(int x, int odd)
{
    int palindrome = x;

    if (odd)
    {
        x /= 10;
    }
    while (x != 0)
    {
        palindrome *= 10;
        palindrome += x % 10;
        x /= 10;
    }

    return palindrome;
}

void AddPrimePalindromesNumberOfDigits(int numberOfDigits, vector<int>& vec)
{
    int halfPalLen = (numberOfDigits + 1) / 2;
    int odd = numberOfDigits % 2;

    int x = 1, endX, xPal;
    for (int i = 0; i < halfPalLen - 1; i++) x *= 10;
    endX = x * 10;

    while (x < endX)
    {
        xPal = GetPalindrome(x, odd);
        if (IsPrime(xPal))
        {
            vec.push_back(xPal);
        }

        x++;
        if (FirstDigit(x) % 2 == 0)
        {
            x += endX / 10;
        }
    }
}

int GetNumberOfDigits(int n)
{
    int numberOfDigits = 0;

    while (n != 0)
    {
        numberOfDigits++;
        n /= 10;
    }

    return numberOfDigits;
}

void PrintPrimePalindromesInterval(int a, int b)
{
    int aNumberOfDigits = GetNumberOfDigits(a);
    int bNumberOfDigits = GetNumberOfDigits(b);

    vector<int> primePalindromes;

    for (int d = aNumberOfDigits; d <= bNumberOfDigits; d++)
    {
        AddPrimePalindromesNumberOfDigits(d, primePalindromes);
    }

    for (int i = 0; i < primePalindromes.size(); i++)
    {
        if (primePalindromes[i] > b)
        {
            return;
        }
        if (primePalindromes[i] >= a)
        {
            fout << primePalindromes[i] << endl;
        }
    }
}
int main()
{
    int a, b;
    fin >> a >> b;

    PrintPrimePalindromesInterval(a, b);

    return 0;
}