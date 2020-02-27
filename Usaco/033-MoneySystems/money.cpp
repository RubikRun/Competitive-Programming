/*
ID: borisd22
TASK: money
LANG: C++
*/

#include <fstream>

using namespace std;

ifstream fin ("money.in");
ofstream fout ("money.out");

#define MaxNumberOfCoins 25
#define MaxSum 10000

int main()
{
    int numberOfCoins;
    fin >> numberOfCoins;

    int wantedSum;
    fin >> wantedSum;

    int coins[MaxNumberOfCoins];
    for (int i = 0; i < numberOfCoins; i++)
    {
        fin >> coins[i];
    }

    long long ways[MaxSum + 1] = {1};
    for (int i = 1; i <= wantedSum; i++)
    {
        ways[i] = 0;
    }
    for (int coinIndex = 0; coinIndex < numberOfCoins; coinIndex++)
    {
        for (int sum = coins[coinIndex]; sum <= wantedSum; sum++)
        {
            ways[sum] += ways[sum - coins[coinIndex]];
        }
    }

    fout << ways[wantedSum] << endl;

    return 0;
}