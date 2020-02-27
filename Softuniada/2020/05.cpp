#include <iostream>
#include <cstring>
using namespace std;

#define MAXMAPLEN 17
char const star = '*';
char const letters[3] = {'L', 'R', 'S'};

int main()
{
    char map[MAXMAPLEN];
    cin >> map;
    int mapLen = strlen(map);

    int starsIndexes[MAXMAPLEN];
    int starsCount = 0;
    for (int i = 0; i < mapLen; i++)
    {
        if (map[i] == star)
        {
            starsIndexes[starsCount++] = i;
        }
    }

    int mapsCount = 1;
    for (int i = 0; i < starsCount; i++)
    {
        mapsCount *= 3;
    }
    cout << mapsCount << endl;

    for (int i = 0; i < mapsCount; i++)
    {
        char currMap[MAXMAPLEN];
        for (int j = 0; j < mapLen; j++)
        {
            if (map[j] != star)
            {
                currMap[j] = map[j];
            }
        }
        int curri = i;
        for (int j = starsCount - 1; j >= 0; j--)
        {
            currMap[starsIndexes[j]] = letters[curri % 3];
            curri /= 3;
        }
        currMap[mapLen] = '\0';
        cout << currMap << endl;
    }

    return 0;
}