/*
ID: borisd22
TASK: ride
LANG: C++                 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int MakeNumber(char s[])
{
    int len = strlen(s);
    int number = 1;
    for (int i = 0; i < len; i++)
    {
        number *= s[i] - 'A' + 1;
    }

    return number % 47;
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");

    char a[8], b[8];
    fin >> a >> b;

    if (MakeNumber(a) == MakeNumber(b))
    {
        fout << "GO" << endl;
    }
    else
    {
        fout << "STAY" << endl;
    }

    return 0;
}
