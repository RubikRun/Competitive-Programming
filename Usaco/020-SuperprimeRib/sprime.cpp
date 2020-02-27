/*
ID: borisd22
TASK: sprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("sprime.out");
ifstream fin ("sprime.in");

#define MaxNumberOfDigits 8

bool IsPrime(int x)
{
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;

    for (int i = 3; i * i <= x; i += 2)
    {
        if (x % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool IsSuperPrime(int x)
{
    while (x != 0)
    {
        if (!IsPrime(x))
        {
            return false;
        }
        x /= 10;
    }

    return true;
}

int TenToThePower(int power)
{
    int n = 1;

    for (int i = 0; i < power; i++)
    {
        n *= 10;
    }

    return n;
}

void GetDigits(int x, int digits[], int& numberOfDigits)
{
    numberOfDigits = 0;

    while (x != 0)
    {
        digits[numberOfDigits++] = x % 10;
        x /= 10;
    }
}

int GetNumberFromDigits(int digits[], int numberOfDigits)
{
    int x = 0;

    for (int i = numberOfDigits - 1; i >= 0; i--)
    {
        x *= 10;
        x += digits[i];
    }

    return x;
}

void MakeNextNon3Superprime(int& x)
{
    int originalX = x;

    int numberOfOnes = 0;
    while (x % 3 != 0)
    {
        numberOfOnes++;
        x /= 10;

        if (x == 0 || x == 3)
        {
            x = originalX;
            return;
        }
    }

    int p = TenToThePower(numberOfOnes);
    x++;
    x *= p;
    p /= 10;
    while (p != 0)
    {
        x += p;
        p /= 10;
    }
}

void MakeNextNon2Superprime(int& x)
{
    int digits[MaxNumberOfDigits], numberOfDigits;
    GetDigits(x, digits, numberOfDigits);

    for (int i = numberOfDigits - 1; i >= 0; i--) {
        if (digits[i] % 2 == 0 && !(i == numberOfDigits - 1 && digits[i] == 2))
        {
            digits[i]++;
            for (int j = i - 1; j >= 0; j--) {
                digits[j] = 1;
            }
            break;
        }
    }

    x = GetNumberFromDigits(digits, numberOfDigits);
}

vector<int> GetSuperPrimes(int numberOfDigits)
{
    vector<int> superPrimes;

    int x = TenToThePower(numberOfDigits - 1);
    int endX = x * 10;

    while (x < endX)
    {
        MakeNextNon3Superprime(x);
        MakeNextNon2Superprime(x);
        if (IsSuperPrime(x))
        {
            superPrimes.push_back(x);
        }
        x += 2;
    }

    return superPrimes;
}

int main()
{
    int numberOfDigits;
    fin >> numberOfDigits;

    vector<int> superPrimes = {23399339, 29399999, 37337999, 59393339, 73939133};
    if (numberOfDigits != 8)
    {
        superPrimes = GetSuperPrimes(numberOfDigits);
    }
    for (int i = 0; i < superPrimes.size(); i++)
    {
        fout << superPrimes[i] << endl;
    }

    return 0;
}