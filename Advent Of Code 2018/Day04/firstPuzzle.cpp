//Works

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Timestamp
{
    int year, month, day, hour, minute;
    int guardID;
    string message;
};

vector<Timestamp> timestamps;
map<int, vector<Timestamp>> guardTimestamps;

bool TimestampComparator(Timestamp& t1, Timestamp& t2)
{
    if (t1.year != t2.year) return t1.year < t2.year;
    if (t1.month != t2.month) return t1.month < t2.month;
    if (t1.day != t2.day) return t1.day < t2.day;
    if (t1.hour != t2.hour) return t1.hour < t2.hour;
    if (t1.minute != t2.minute) return t1.minute < t2.minute;
}

Timestamp GetTimestamp(string s)
{
    Timestamp timestamp = {0, 0, 0, 0, 0, -1};

    int i = 1;
    while (s[i] != '-')
    {
        timestamp.year *= 10;
        timestamp.year += s[i++] - '0';
    }
    i++;
    while (s[i] != '-')
    {
        timestamp.month *= 10;
        timestamp.month += s[i++] - '0';
    }
    i++;
    while (s[i] != ' ')
    {
        timestamp.day *= 10;
        timestamp.day += s[i++] - '0';
    }
    i++;
    while (s[i] != ':')
    {
        timestamp.hour *= 10;
        timestamp.hour += s[i++] - '0';
    }
    i++;
    while (s[i] != ']')
    {
        timestamp.minute *= 10;
        timestamp.minute += s[i++] - '0';
    }
    i += 2;

    timestamp.message = s.substr(i);
    while (s[i] != '#')
    {
        if (i == s.length() - 1)
        {
            return timestamp;
        }
        i++;
    }
    i++;
    timestamp.guardID = 0;
    while (s[i] != ' ')
    {
        timestamp.guardID *= 10;
        timestamp.guardID += s[i++] - '0';
    }

    return timestamp;
}

void ReadTimeStamps()
{
    while (true)
    {
        string input;
        getline(cin, input);

        if (input == "end")
        {
            break;
        }

        Timestamp timestamp = GetTimestamp(input);
        timestamps.push_back(timestamp);
    }
}

void AssignGuardsToTimestamps()
{
    int lastGuardID = -1;
    for (int i = 0; i < timestamps.size(); i++)
    {
        if (timestamps[i].guardID == -1)
        {
            timestamps[i].guardID = lastGuardID;
        }
        else
        {
            lastGuardID = timestamps[i].guardID;
        }
    }
}

void FillGuardTimestamps()
{
    for (int i = 0; i < timestamps.size(); i++)
    {
        guardTimestamps[timestamps[i].guardID].push_back(timestamps[i]);
    }
}

int GetGuardTotalSleepTime(int guardID)
{
    int sleepTime = 0;

    for (int i = 0; i < guardTimestamps[guardID].size(); i++)
    {
        Timestamp timestamp = guardTimestamps[guardID][i];
        if (timestamp.message == "falls asleep")
        {
            Timestamp nextTimestamp = guardTimestamps[guardID][i + 1];
            sleepTime += nextTimestamp.minute - timestamp.minute;
        }
    }

    return sleepTime;
}

int GetSleepiestGuardID()
{
    int sleepiestGuardID = -1;

    int mostSleep = 0;
    for (map<int, vector<Timestamp>>::iterator i = guardTimestamps.begin(); i != guardTimestamps.end(); i++)
    {
        int currSleep = GetGuardTotalSleepTime((*i).first);
        if (currSleep > mostSleep)
        {
            mostSleep = currSleep;
            sleepiestGuardID = (*i).first;
        }
    }

    return sleepiestGuardID;
}

int GetSleepiestMinute(int guardID)
{
    const int numberOfMinutes = 60;
    int slept[numberOfMinutes];
    for (int i = 0; i < numberOfMinutes; i++)
    {
        slept[i] = 0;
    }

    for (int i = 0; i < guardTimestamps[guardID].size(); i++)
    {
        Timestamp timestamp = guardTimestamps[guardID][i];
        if (timestamp.message == "falls asleep")
        {
            Timestamp nextTimestamp = guardTimestamps[guardID][i + 1];
            for (int j = timestamp.minute; j < nextTimestamp.minute; j++)
            {
                slept[j]++;
            }
        }
    }

    int sleepiestMinute = 0;
    for (int i = 1; i < numberOfMinutes; i++)
    {
        if (slept[i] > slept[sleepiestMinute])
        {
            sleepiestMinute = i;
        }
    }

    return sleepiestMinute;
}

void PrintTimestamp(Timestamp& t)
{
    cout << t.year << " " << t.month << " " << t.day << " " << t.hour << " " << t.minute << " " << t.guardID << " " << t.message << endl;
}

int main()
{
    ReadTimeStamps();
    sort(timestamps.begin(), timestamps.end(), TimestampComparator);
    AssignGuardsToTimestamps();
    FillGuardTimestamps();

    int sleepiestGuardID = GetSleepiestGuardID();
    int sleepiestMinute = GetSleepiestMinute(sleepiestGuardID);

    cout << sleepiestGuardID * sleepiestMinute << endl;

    return 0;
}
