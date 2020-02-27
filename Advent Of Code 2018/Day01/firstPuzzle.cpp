//Works

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int result = 0;

    while (true)
    {
        string input;
        cin >> input;

        if (input == "end")
        {
            break;
        }

        result += stoi(input);
    }

    cout << result << endl;

    return 0;
}
