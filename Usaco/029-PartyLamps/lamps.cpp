/*
ID: borisd22
TASK: lamps
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("lamps.out");
ifstream fin ("lamps.in");

#define MaxNumberOfLamps 100

int numberOfLamps, numberOfActions;
int lamps[MaxNumberOfLamps + 1];

void PrintPossibleConfigurations(vector< vector<int> > configurations)
{
    bool found = false;

    for (int i = 0; i < configurations.size(); i++)
    {
        bool isPossible = true;
        for (int j = 1; j <= numberOfLamps; j++)
        {
            if (lamps[j] == -1)
            {
                continue;
            }

            if (lamps[j] != configurations[i][(j - 1) % configurations[i].size()])
            {
                isPossible = false;
                break;
            }
        }

        if (isPossible)
        {
            found = true;
            for (int j = 1; j <= numberOfLamps; j++)
            {
                fout << configurations[i][(j - 1) % configurations[i].size()];
            }
            fout << endl;
        }
    }

    if (!found)
    {
        fout << "IMPOSSIBLE" << endl;
    }
}

int main()
{
    fin >> numberOfLamps;
    fin >> numberOfActions;

    //Initializing all lamps with -1 (unknown value)
    for (int i = 1; i <= numberOfLamps; i++)
    {
        lamps[i] = -1;
    }

    //Reading and setting ON lamps
    int currentLamp = 0;
    while (true)
    {
        fin >> currentLamp;
        if (currentLamp == -1)
        {
            break;
        }

        lamps[currentLamp] = 1;
    }

    //Reading and setting OFF lamps
    currentLamp = 0;
    while (true)
    {
        fin >> currentLamp;
        if (currentLamp == -1)
        {
            break;
        }

        lamps[currentLamp] = 0;
    }


    vector< vector<int> > configurations;
    if (numberOfActions == 1)
    {
        configurations = {{0}, {0, 1}, {0, 1, 1}, {1, 0}};
    }
    else if (numberOfActions == 2)
    {
        configurations = {{0}, {0, 0, 1, 1, 1, 0}, {0, 1}, {1, 0, 0}, {1, 0}, {1, 1, 0, 0, 0, 1}};
    }
    else
    {
        configurations = {{0}, {0, 0, 1, 1, 1, 0}, {0, 1}, {0, 1, 1}, {1, 0, 0}, {1, 0}, {1, 1, 0, 0, 0, 1}};
    }
    if (numberOfActions % 2 == 0)
    {
        if (numberOfActions == 0)
        {
            configurations.clear();
        }
        configurations.push_back({1});
    }

    PrintPossibleConfigurations(configurations);

    return 0;
}