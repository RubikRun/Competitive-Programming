#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define MaxWordLen 100
#define AlphabetLen 26

int main()
{
    char word[MaxWordLen + 1];
    cin >> word;
    int wordLen = strlen(word);

    int rotations = min(word[0] - 'a', 'z' + 1 - word[0]);
    for (int i = 1; i < wordLen; i++)
    {
        rotations += min(abs(word[i - 1] - word[i]), AlphabetLen - abs(word[i - 1] - word[i]));
    }

    cout << rotations << endl;

    return 0;
}
