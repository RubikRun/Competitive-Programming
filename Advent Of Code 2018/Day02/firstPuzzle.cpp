//Works

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define NumberOfLetters 26

vector<string> IDs;

void ReadIDs()
{
    while (true)
    {
        string input;
        cin >> input;

        if (input == "end")
        {
            break;
        }

        IDs.push_back(input);
    }
}

//returns a type
//type.first indicates whether there is a double letter (0 or 1)
//type.second indicates whether there is a triple letter (0 or 1)
pair<int, int> GetType(string ID)
{
    pair<bool, bool> type = {0, 0};

    int count[NumberOfLetters];
    for (int i = 0; i < NumberOfLetters; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < ID.length(); i++)
    {
        count[ID[i] - 'a']++;
    }

    for (int i = 0; i < NumberOfLetters; i++)
    {
        if (count[i] == 2)
        {
            type.first = 1;
        }
        else if (count[i] == 3)
        {
            type.second = 1;
        }
    }

    return type;
}

int GetChecksum()
{
    int numberOfDoubles = 0;
    int numberOfTriples = 0;

    for (int i = 0; i < IDs.size(); i++)
    {
        pair<bool, bool> type = GetType(IDs[i]);
        numberOfDoubles += type.first;
        numberOfTriples += type.second;
    }

    return numberOfDoubles * numberOfTriples;
}

int main()
{
    ReadIDs();

    cout << GetChecksum() << endl;

    return 0;
}
