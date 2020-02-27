//Works

#include <iostream>
#include <vector>

using namespace std;

int GetRootValue()
{
    int numberOfChildren, numberOfMetadata;
    cin >> numberOfChildren >> numberOfMetadata;

    vector<int> childrenValues = {-1};
    for (int i = 1; i <= numberOfChildren; i++)
    {
        childrenValues.push_back(GetRootValue());
    }

    int rootValue = 0;
    for (int i = 0; i < numberOfMetadata; i++)
    {
        int metadata;
        cin >> metadata;

        if (numberOfChildren == 0)
        {
            rootValue += metadata;
            continue;
        }
        if (metadata < 1 || metadata > numberOfChildren)
        {
            continue;
        }
        rootValue += childrenValues[metadata];
    }

    return rootValue;
}

int main()
{
    cout << GetRootValue() << endl;

    return 0;
}
