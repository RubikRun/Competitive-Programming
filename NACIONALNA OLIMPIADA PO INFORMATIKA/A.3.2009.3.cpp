#include <iostream>
#include <vector>

using namespace std;
#define MaxNumberOfRows 1000
#define MaxNumberOfCols 1000
#define Unknown -7797818

int tab[MaxNumberOfRows][MaxNumberOfCols];
int numberOfRows;
int numberOfCols;

struct Entry
{
    int row;
    int col;
};

vector<Entry> GetEntryFriends(Entry entry)
{
    vector<Entry> friends;

    if (entry.row > 0)
    {
        friends.push_back({entry.row - 1, entry.col});
    }
    if (entry.row + 1 < numberOfRows)
    {
        friends.push_back({entry.row + 1, entry.col});
    }
    if (entry.col > 0)
    {
        friends.push_back({entry.row, entry.col - 1});
    }
    if (entry.col + 1 < numberOfCols)
    {
        friends.push_back({entry.row, entry.col + 1});
    }

    return friends;
}

void InitTab()
{
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfCols; j++)
        {
            tab[i][j] = Unknown;
        }
    }
}

Entry GetHighEntry(Entry root)
{
    if (tab[root.row][root.col] == Unknown)
    {
        cout << 0 << " " << root.row << " " << root.col << endl;
        cin >> tab[root.row][root.col];
    }

    vector<Entry> friends = GetEntryFriends(root);
    Entry higherFriend = {Unknown, Unknown};
    for (int i = 0; i < friends.size(); i++)
    {
        if (tab[friends[i].row][friends[i].col] == Unknown)
        {
            cout << 0 << " " << friends[i].row << " " << friends[i].col << endl;
            cin >> tab[friends[i].row][friends[i].col];
        }
        if (higherFriend.row == Unknown)
        {
            if (tab[friends[i].row][friends[i].col] > tab[root.row][root.col])
            {
                higherFriend = friends[i];
            }
        }
        else if (tab[friends[i].row][friends[i].col] > tab[higherFriend.row][higherFriend.col])
        {
            higherFriend = friends[i];
        }
    }

    if (higherFriend.row == Unknown)
    {
        return root;
    }
    else
    {
        return GetHighEntry(higherFriend);
    }
}

int main()
{
    cin >> numberOfRows >> numberOfCols;
    InitTab();

    Entry highEntry = GetHighEntry({0, 0});
    cout << 1 << " " << highEntry.row << " " << highEntry.col << endl;

    return 0;
}
