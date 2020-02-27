#include <iostream>
#include <cstring>
using namespace std;

#define MAXSEQLEN 10000
#define MAXSEQSTRLEN (MAXSEQLEN * 2)
#define MAXCOMMANDLEN 100

char aStr[MAXSEQSTRLEN];
char bStr[MAXSEQSTRLEN];
int a[MAXSEQLEN], aLen;
int b[MAXSEQLEN], bLen;

void Swap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

void ReadSeqStrs()
{
    cin.getline(aStr, MAXSEQSTRLEN);
    cin.getline(bStr, MAXSEQSTRLEN);
}

int GetNumFromSubstring(char* str, int first, int last)
{
    int result = 0;
    for (int i = first; i <= last; i++)
    {
        result = result * 10 + str[i] - '0';
    }
    return result;
}

void ParseSeqStrs()
{
    aLen = bLen = 0;

    int currNumBegin = 0;
    for (int i = 0; i < strlen(aStr); i++)
    {
        if (aStr[i] == ' ')
        {
            a[aLen++] = GetNumFromSubstring(aStr, currNumBegin, i - 1);
            currNumBegin = i + 1;
        }
    }
    a[aLen++] = GetNumFromSubstring(aStr, currNumBegin, strlen(aStr) - 1);

    currNumBegin = 0;
    for (int i = 0; i < strlen(bStr); i++)
    {
        if (bStr[i] == ' ')
        {
            b[bLen++] = GetNumFromSubstring(bStr, currNumBegin, i - 1);
            currNumBegin = i + 1;
        }
    }
    b[bLen++] = GetNumFromSubstring(bStr, currNumBegin, strlen(bStr) - 1);
}

void ParseCommand(char* command, int& a1, int& b1, int& a2, int& b2)
{
    int nums[4];
    int numCount = 0;

    int currNumBegin = 0;
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == ':' || command[i] == '|')
        {
            nums[numCount++] = GetNumFromSubstring(command, currNumBegin, i - 1);
            currNumBegin = i + 1;
        }
    }
    nums[numCount++] = GetNumFromSubstring(command, currNumBegin, strlen(command) - 1);

    a1 = nums[0];
    b1 = nums[1];
    a2 = nums[2];
    b2 = nums[3];
}

bool TheyCross(int a1, int b1, int a2, int b2)
{
    return (a2 < a1 && b2 > b1) || (a2 > a1 && b2 < b1);
}

void NexusStep(int a1, int b1, int a2, int b2)
{
    int nexusSum = a[a1] + b[b1] + a[a2] + b[b2];

    if (a1 > a2) Swap(a1, a2);
    if (b1 > b2) Swap(b1, b2);

    for (int i = 0; i < a1; i++)
    {
        a[i] += nexusSum;
    }
    for (int i = a1; i < aLen - (a2 - a1 + 1); i++)
    {
        a[i] = a[i + (a2 - a1 + 1)] + nexusSum;
    }

    for (int i = 0; i < b1; i++)
    {
        b[i] += nexusSum;
    }
    for (int i = b1; i < bLen - (b2 - b1 + 1); i++)
    {
        b[i] = b[i + (b2 - b1 + 1)] + nexusSum;
    }

    aLen -= (a2 - a1 + 1);
    bLen -= (b2 - b1 + 1);
}

int main()
{
    ReadSeqStrs();
    ParseSeqStrs();

    char command[MAXCOMMANDLEN];
    int a1, b1, a2, b2;
    while (true)
    {
        cin >> command;
        if (strcmp(command, "nexus") == 0)
        {
            break;
        }
        ParseCommand(command, a1, b1, a2, b2);

        if (TheyCross(a1, b1, a2, b2))
        {
            NexusStep(a1, b1, a2, b2);
        }      
    }

    for (int i = 0; i < aLen - 1; i++)
    {
        cout << a[i] << ", ";
    }
    cout << a[aLen - 1] << endl;

    for (int i = 0; i < bLen - 1; i++)
    {
        cout << b[i] << ", ";
    }
    cout << b[bLen - 1] << endl;

    return 0;
}