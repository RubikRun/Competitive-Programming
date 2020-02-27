/*
ID: borisd22
TASK: runround
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout ("runround.out");
ifstream fin ("runround.in");

bool HasUniqueDigits(long long unsigned n)
{
    bool digit[10]; for (int i = 0; i < 10; i++) digit[i] = false;

    while (n != 0)
    {
        if (digit[n % 10])
        {
            return false;
        }
        digit[n % 10] = true;
        n /= 10;
    }

    return !digit[0];
}

vector<int> GetDigits(long long unsigned n)
{
    vector<int> digits;

    while (n != 0)
    {
        digits.push_back(n % 10);
        n /= 10;
    }

    reverse(digits.begin(), digits.end());

    return digits;
}

bool IsRunaround(long long unsigned n)
{
    if (!HasUniqueDigits(n))
    {
        return false;
    }

    vector<int> digits = GetDigits(n);

    int beenToDigit[10]; for (int i = 0; i < digits.size(); i++) beenToDigit[i] = false;
    int i = 0;
    do
    {
        i = (i + digits[i]) % digits.size();
        if (beenToDigit[i])
        {
            return false;
        }
        beenToDigit[i] = true;
    } while (i != 0);

    for (i = 0; i < digits.size(); i++)
    {
        if (!beenToDigit[i])
        {
            return false;
        }
    }

    return true;
}

long long unsigned NextRunaroundNumber(long long unsigned n)
{
    do
    {
        n++;
    } while (!IsRunaround(n));

    return n;
}

int main()
{
    unsigned long long n;
    fin >> n;

    fout << NextRunaroundNumber(n) << endl;

    return 0;
}