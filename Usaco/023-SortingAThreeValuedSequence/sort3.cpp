/*
ID: borisd22
TASK: sort3
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout ("sort3.out");
ifstream fin ("sort3.in");

#define MaxLen 1000

int main()
{
    int arr[MaxLen];
    int numberOfOnes = 0, numberOfTwos = 0;

    int len;
    fin >> len;
    for (int i = 0; i < len; i++)
    {
        fin >> arr[i];
        if (arr[i] == 1)
        {
            numberOfOnes++;
        }
        else if (arr[i] == 2)
        {
            numberOfTwos++;
        }
    }

    int numberOfExchanges = 0;
    int numberOfTwosInOneZone = 0;
    for (int i = 0; i < len; i++)
    {
        if (i < numberOfOnes)
        {
            if (arr[i] == 2)
            {
                numberOfTwosInOneZone++;
            }
        }
        else
        {
            if (arr[i] == 1)
            {
                if (numberOfTwosInOneZone > 0)
                {
                    arr[i] = 2;
                    numberOfTwosInOneZone--;
                }
                else
                {
                    arr[i] = 3;
                }
                numberOfExchanges++;
            }
        }
    }

    for (int i = numberOfOnes; i < numberOfOnes + numberOfTwos; i++)
    {
        if (arr[i] == 3)
        {
            numberOfExchanges++;
        }
    }

    fout << numberOfExchanges << endl;

    return 0;
}