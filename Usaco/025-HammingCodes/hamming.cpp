/*
ID: borisd22
TASK: hamming
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("hamming.out");
ifstream fin ("hamming.in");

#define MaxNumberOfBits 8

int TwoToThe(int power)
{
    int result = 1;

    for (int i = 0; i < power; i++)
    {
        result *= 2;
    }

    return result;
}

int GetHammingDistance(int a, int b)
{
    int hammingDistance = 0;

    while (a != 0 || b != 0)
    {
        if (a % 2 != b % 2)
        {
            hammingDistance++;
        }
        a /= 2;
        b /= 2;
    }

    return hammingDistance;
}

bool EnoughHammingDistance(int newCodeword, vector<int>& codewords, int minHammingDistance)
{
    for (int i = 0; i < codewords.size(); i++)
    {
        if (GetHammingDistance(newCodeword, codewords[i]) < minHammingDistance)
        {
            return false;
        }
    }

    return true;
}

vector<int> GetCodewords(int numberOfCodewords, int numberOfBits, int minHammingDistance)
{
    if (numberOfCodewords == 1)
    {
        return {0};
    }

    vector<int> codewords = {0};

    int maxCodeword = TwoToThe(numberOfBits);
    for (int potentialCodeword = 1; potentialCodeword <= maxCodeword && codewords.size() < numberOfCodewords; potentialCodeword++)
    {
        if (EnoughHammingDistance(potentialCodeword, codewords, minHammingDistance))
        {
            codewords.push_back(potentialCodeword);
        }
    }

    return codewords;
}

int main()
{
    //input
    int numberOfCodewords;
    fin >> numberOfCodewords;

    int numberOfBits;
    fin >> numberOfBits;

    int minHammingDistance;
    fin >> minHammingDistance;

    //solution
    vector<int> codewords = GetCodewords(numberOfCodewords, numberOfBits, minHammingDistance);

    //output
    for (int i = 0; i < codewords.size() - 1; i++)
    {
        fout << codewords[i];
        if ((i + 1) % 10 == 0)
        {
            fout << endl;
        }
        else
        {
            fout << " ";
        }
    }
    fout << codewords.back() << endl;

    return 0;
}