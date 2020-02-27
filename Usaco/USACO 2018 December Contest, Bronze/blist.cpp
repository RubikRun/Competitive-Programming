/*
ID: borisd22
TASK: blist
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfEvents 200

ifstream fin ("blist.in");
ofstream fout ("blist.out");

struct Event
{
    int time;
    int buckets;

    bool operator< (const Event& x) const
    {
        return time < x.time;
    }
};

Event events[MaxNumberOfEvents];
int numberOfEvents;

void Input()
{
    int numberOfCows;
    Read >> numberOfCows;
    numberOfEvents = numberOfCows * 2;

    for (int i = 0; i < numberOfCows; i++)
    {
        int startTime, finishTime, buckets;
        Read >> startTime >> finishTime >> buckets;

        events[i * 2].time = startTime;
        events[i * 2].buckets = buckets;
        events[i * 2 + 1].time = finishTime;
        events[i * 2 + 1].buckets = -buckets;
    }
}

int GetNeededBuckets()
{
    sort(events, events + numberOfEvents);

    int neededBuckets = 0;
    int currBuckets = 0;
    for (int i = 0; i < numberOfEvents; i++)
    {
        currBuckets += events[i].buckets;
        neededBuckets = max(neededBuckets, currBuckets);
    }

    return neededBuckets;
}

int main()
{
    Input();

    Write << GetNeededBuckets() << endl;

    return 0;
}
