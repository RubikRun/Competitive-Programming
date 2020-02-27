/*
ID: borisd22
TASK: numtri
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("numtri.out");
ifstream fin ("numtri.in");

#define MaxNumberOfRows 1000

int main()
{
    int numberOfRows;
    fin >> numberOfRows;

    int triangle[MaxNumberOfRows][MaxNumberOfRows];
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int col = 0; col < row + 1; col++)
        {
            fin >> triangle[row][col];
        }
    }

    int maxSum[MaxNumberOfRows][MaxNumberOfRows];
    for (int row = numberOfRows - 1; row >= 0; row--)
    {
        for (int col = 0; col < row + 1; col++)
        {
            if (row == numberOfRows - 1)
            {
                maxSum[row][col] = triangle[row][col];
            }
            else
            {
                maxSum[row][col] = max(maxSum[row + 1][col], maxSum[row + 1][col + 1]) + triangle[row][col];
            }
        }
    }

    fout << maxSum[0][0] << endl;

    return 0;
}