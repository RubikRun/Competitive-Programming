//checked - 100%

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MaxNumberOfDigits 62

struct Number
{
    int numberOfDigits;
    vector<int> possibleDigits[MaxNumberOfDigits];
};

Number A, B, C;

void ReadNumber(Number& number)
{
    char inputDigits[MaxNumberOfDigits];
    scanf("%s", inputDigits);

    number.numberOfDigits = (int)strlen(inputDigits);

    for (int i = 0; i < number.numberOfDigits; i++)
    {
        if (inputDigits[i] == '?')
        {
            number.possibleDigits[number.numberOfDigits - 1 - i] = {0, 1};
        }
        else
        {
            number.possibleDigits[number.numberOfDigits - 1 - i] = {inputDigits[i] - '0'};
        }
    }
    for (int i = number.numberOfDigits; i < MaxNumberOfDigits; i++)
    {
        number.possibleDigits[i] = {0};
    }
}

void PrintNumber(Number& number)
{
    for (int i = number.numberOfDigits - 1; i >= 0; i--)
    {
        if (number.possibleDigits[i].size() == 1)
        {
            printf("%d", number.possibleDigits[i][0]);
        }
        else
        {
            printf("?");
        }
    }
    printf("\n");
}

void AddIfNew(vector<int>& vec, int el)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == el)
        {
            return;
        }
    }

    vec.push_back(el);
}

void CopyVector(vector<int>& vec1, vector<int>& vec2)
{
    vec2.clear();

    for (int i = 0; i < vec1.size(); i++)
    {
        vec2.push_back(vec1[i]);
    }
}

void CalculateC()
{
    vector<int> carry = {0};
    vector<int> nextCarry;

    C.numberOfDigits = 0;
    for (int i = 0; i < max(A.numberOfDigits, B.numberOfDigits) || !(carry.size() == 1 && carry[0] == 0); i++, C.numberOfDigits++)
    {
        nextCarry.clear();

        for (int ai = 0; ai < A.possibleDigits[i].size(); ai++)
        {
            for (int bi = 0; bi < B.possibleDigits[i].size(); bi++)
            {
                for (int carryi = 0; carryi < carry.size(); carryi++)
                {
                    AddIfNew(C.possibleDigits[i], (A.possibleDigits[i][ai] + B.possibleDigits[i][bi] + carry[carryi]) % 2);
                    AddIfNew(nextCarry, (A.possibleDigits[i][ai] + B.possibleDigits[i][bi] + carry[carryi]) / 2);
                }
            }
        }
        CopyVector(nextCarry, carry);
    }
}

int main()
{
    ReadNumber(A);
    ReadNumber(B);

    CalculateC();

    PrintNumber(C);

    return 0;
}