//Works

#include <iostream>

using namespace std;

int GetTreeSum()
{
    int numberOfChildren, numberOfMetadata;
    cin >> numberOfChildren >> numberOfMetadata;

    int treeSum = 0;
    for (int i = 0; i < numberOfChildren; i++)
    {
        treeSum += GetTreeSum();
    }

    for (int i = 0; i < numberOfMetadata; i++)
    {
        int metadata;
        cin >> metadata;
        treeSum += metadata;
    }

    return treeSum;
}

int main()
{
    cout << GetTreeSum() << endl;

    return 0;
}
