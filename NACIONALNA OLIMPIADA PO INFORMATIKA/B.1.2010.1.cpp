//checked - 100%

#include <cstdio>
#include <cstring>

using namespace std;

#define MaxWordLength 20
#define MaxNumberOfWords 99

int LetterToNumber(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 1;
    }
    return c - 'A' + 1;
}

unsigned CalculateWordWeight(char word[], unsigned wordLength)
{
    unsigned wordWeight = 0;

    for (int index = wordLength - 1; index >= 0; index--)
    {
        wordWeight *= 2;
        wordWeight += LetterToNumber(word[index]);
    }

    return wordWeight;
}

int main()
{
    int numberOfWords;
    scanf("%u", &numberOfWords);

    char words[MaxNumberOfWords][MaxWordLength];
    for (int wordIndex = 0; wordIndex < numberOfWords; wordIndex++)
    {
        scanf("%s", words[wordIndex]);
    }

    unsigned heaviestWordIndex = 0, heaviestWordWeight = CalculateWordWeight(words[0], strlen(words[0]));
    unsigned currentWordWeight;
    for (int wordIndex = 1; wordIndex < numberOfWords; wordIndex++)
    {
        currentWordWeight = CalculateWordWeight(words[wordIndex], strlen(words[wordIndex]));
        if (currentWordWeight > heaviestWordWeight)
        {
            heaviestWordIndex = wordIndex;
            heaviestWordWeight = currentWordWeight;
        }
    }

    printf("%s\n", words[heaviestWordIndex]);
    return 0;
}