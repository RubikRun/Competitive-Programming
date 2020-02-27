//Works

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define NumberOfLetters 26

vector<string> IDs;

void Input()
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

string GetCommonPart()
{
    for (int i = 0; i < IDs.size() - 1; i++)
    {
        for (int j = i + 1; j < IDs.size(); j++)
        {
            if (IDs[i].length() != IDs[j].length())
            {
                continue;
            }

            string result = "";
            int diffCount = 0;
            for (int k = 0; k < IDs[i].length(); k++)
            {
                if (IDs[i][k] != IDs[j][k])
                {
                    diffCount++;
                    if (diffCount >= 2)
                    {
                        break;
                    }
                }
                else
                {
                    result += IDs[i][k];
                }
            }

            if (diffCount < 2)
            {
                return result;
            }
        }
    }

    return "Error";
}

int main()
{
    Input();

    cout << GetCommonPart() << endl;

    return 0;
}
