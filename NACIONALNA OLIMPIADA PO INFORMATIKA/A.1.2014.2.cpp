//checked - 100%

#include <cstdio>
#include <cstring>

using namespace std;

#define MaxNumberOfLetters 26
#define MaxPowerNeeded 26
#define nm(a, b) (nPower[a] * mPower[b])

long long nPower[MaxPowerNeeded];
long long mPower[MaxPowerNeeded];

char allLetters[MaxNumberOfLetters];
int numberOfAllLetters;
char consonants[MaxNumberOfLetters];
int numberOfConsonants;
char vowels[MaxNumberOfLetters];
int numberOfVowels;

void InitPowers()
{
    nPower[0] = 1;
    mPower[0] = 1;

    for (int i = 1; i < MaxPowerNeeded; i++)
    {
        nPower[i] = nPower[i - 1] * numberOfConsonants;
        mPower[i] = mPower[i - 1] * numberOfVowels;
    }
}

void ReadLetters()
{
    scanf("%s", allLetters);
    numberOfAllLetters = (int)strlen(allLetters);

    char inputVowels[MaxNumberOfLetters];
    scanf("%s", inputVowels);
    int numberOfInputVowels = (int)strlen(inputVowels);

    numberOfVowels = 0;
    numberOfConsonants = 0;
    for (int i = 0; i < numberOfAllLetters; i++)
    {
        bool isVowel = false;
        for (int j = 0; j < numberOfInputVowels; j++)
        {
            if (allLetters[i] == inputVowels[j])
            {
                isVowel = true;
                break;
            }
        }

        if (isVowel)
        {
            vowels[numberOfVowels++] = allLetters[i];
        }
        else
        {
            consonants[numberOfConsonants++] = allLetters[i];
        }
    }
}

void FindWord(char word[], int k, int index)
{
    for (int i = 0; i < k; i++)
    {
        word[2 * i] = consonants[index % nm(k-i, k-i) / nm(k-i-1, k-i)];
        word[2 * i + 1] = vowels[index % nm(k-i-1, k-i) / nm(k-i-1, k-i-1)];
    }
}

int main()
{
    ReadLetters();
    InitPowers();

    int index;
    scanf("%d", &index);
    index--;

    int numberOfSyllables = 1;
    while (nm(numberOfSyllables, numberOfSyllables) <= index)
    {
        index -= nm(numberOfSyllables, numberOfSyllables);
        numberOfSyllables++;
    }

    char word[MaxNumberOfLetters];
    FindWord(word, numberOfSyllables, index);

    for (int i = 0; i < 2 * numberOfSyllables; i++)
    {
        printf("%c", word[i]);
    }
    printf("\n");

    return 0;
}