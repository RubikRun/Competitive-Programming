//Works

#include <iostream>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

int main()
{
    vector<int> changes;

    while (true)
    {
        string input;
        cin >> input;

        if (input == "end")
        {
            break;
        }

        changes.push_back(stoi(input));
    }

    int result = 0;
    set<int> results;
    results.insert(result);

    int changeIndex = 0;

    while (true)
    {
        result += changes[changeIndex];

        if (results.count(result))
        {
            cout << result << endl;
            return 0;
        }
        results.insert(result);

        changeIndex++;
        if (changeIndex == changes.size())
        {
            changeIndex = 0;
        }
    }
}
