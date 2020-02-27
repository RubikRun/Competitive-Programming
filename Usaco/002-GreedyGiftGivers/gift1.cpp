/*
ID: borisd22
TASK: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ofstream fout ("gift1.out");
ifstream fin ("gift1.in");

#define MaxNumberOfPeople 10
#define MaxNameLen 14

struct Person
{
    char name[MaxNameLen];
    Person* friends[MaxNumberOfPeople];
    int numberOfFriends;
    int money;
    int moneyToReceive;
    int moneyInBeginning;
};

Person people[MaxNumberOfPeople];
int numberOfPeople;

int NameToIndex(char wantedName[])
{
    for (int personIndex = 0; personIndex < numberOfPeople; personIndex++)
    {
        if (strcmp(people[personIndex].name, wantedName) == 0)
        {
            return personIndex;
        }
    }
    return -1;
}

void ReadPeople()
{
    fin >> numberOfPeople;

    for (int personIndex = 0; personIndex < numberOfPeople; personIndex++)
    {
        fin >> people[personIndex].name;
        people[personIndex].moneyToReceive = 0;
    }

    for (int counter = 0; counter < numberOfPeople; counter++)
    {
        char currentPersonName[MaxNameLen];
        fin >> currentPersonName;
        int personIndex = NameToIndex(currentPersonName);

        fin >> people[personIndex].money;
        people[personIndex].moneyInBeginning = people[personIndex].money;
        fin >> people[personIndex].numberOfFriends;

        for (int eachFriend = 0; eachFriend < people[personIndex].numberOfFriends; eachFriend++)
        {
            fin >> currentPersonName;
            int friendIndex = NameToIndex(currentPersonName);
            people[personIndex].friends[eachFriend] = &people[friendIndex];
        }
    }
}

void ExchangeMoney()
{
    for (int personIndex = 0; personIndex < numberOfPeople; personIndex++)
    {
        if (people[personIndex].numberOfFriends == 0)
        {
            continue;
        }
        int moneyToGiveToEachFriend = people[personIndex].money / people[personIndex].numberOfFriends;
        people[personIndex].money = people[personIndex].money % people[personIndex].numberOfFriends;
        for (int friendIndex = 0; friendIndex < people[personIndex].numberOfFriends; friendIndex++)
        {
            people[personIndex].friends[friendIndex]->moneyToReceive += moneyToGiveToEachFriend;
        }
    }

    for (int personIndex = 0; personIndex < numberOfPeople; personIndex++)
    {
        people[personIndex].money += people[personIndex].moneyToReceive;
    }
}

void PrintAnswer()
{
    for (int personIndex = 0; personIndex < numberOfPeople; personIndex++)
    {
        fout << people[personIndex].name << " " << people[personIndex].money - people[personIndex].moneyInBeginning << endl;
    }
}



int main()
{
    ReadPeople();
    ExchangeMoney();
    PrintAnswer();
    return 0;
}