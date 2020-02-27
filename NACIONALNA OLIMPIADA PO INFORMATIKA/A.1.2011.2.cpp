//checked - 100%

#include <cstdio>
#include <cmath>

using namespace std;

#define MaxNumberOfLines 1000

int GCD(int a, int b)
{
    int t;
    while (b != 0)
    {
        t = a;
        a = b;
        b = t % b;
    }

    return a;
}

struct Line
{
    int a;
    int b;
    int c;
};

Line ReadLine() {
    Line line;

    scanf("%d", &line.a);
    scanf("%d", &line.b);
    scanf("%d", &line.c);

    return line;
}

//ax+by+c=0

void SimplifyFraction(int& p, int& q)
{
    if (q < 0)
    {
        p *= (-1);
        q *= (-1);
    }
    int g = GCD(abs(p), abs(q));

    p /= g;
    q /= g;
}

bool FractionsAreEqual(int p1, int q1, int p2, int q2)
{
    SimplifyFraction(p1, q1);
    SimplifyFraction(p2, q2);

    return p1 == p2 && q1 == q2;
}

bool SlopesAreSame(Line& line1, Line& line2)
{
    if (line1.b == 0 && line2.b == 0)
    {
        return true;
    }
    if (line1.b == 0 ^ line2.b == 0)
    {
        return false;
    }
    if (line1.a == 0 && line2.a == 0)
    {
        return true;
    }
    if (line1.a == 0 ^ line2.a == 0)
    {
        return false;
    }

    return FractionsAreEqual(line1.a, line1.b, line2.a, line2.b);
}

bool LinesAreSame(Line& line1, Line& line2)
{
    if (!SlopesAreSame(line1, line2))
    {
        return false;
    }
    if (line1.b == 0)
    {
        return FractionsAreEqual(line1.c, line1.a, line2.c, line2.a);
    }

    return FractionsAreEqual(line1.c, line1.b, line2.c, line2.b);
}

Line lines[MaxNumberOfLines];
int numberOfLines;

Line slopes[MaxNumberOfLines];
int numberOfSlopes;

void AddLineIfNew(Line& line)
{
    for (int i = 0; i < numberOfLines; i++)
    {
        if (LinesAreSame(lines[i], line))
        {
            return;
        }
    }

    lines[numberOfLines++] = line;
}

void AddSlopeIfNew(Line& line)
{
    for (int i = 0; i < numberOfSlopes; i++)
    {
        if (SlopesAreSame(slopes[i], line))
        {
            return;
        }
    }

    slopes[numberOfSlopes++] = line;
}

int main()
{
    numberOfLines = numberOfSlopes = 0;

    int numberOfInputLines;
    scanf("%d", &numberOfInputLines);

    Line currentLine;
    for (int i = 0; i < numberOfInputLines; i++)
    {
        currentLine = ReadLine();
        AddLineIfNew(currentLine);
        AddSlopeIfNew(currentLine);
    }

    printf("%d\n", numberOfLines);
    printf("%d\n", numberOfSlopes);

    return 0;
}

