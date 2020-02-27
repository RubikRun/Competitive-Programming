/*
ID: borisd22
TASK: convention2
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;
#define Read fin
#define Write fout
#define MaxNumberOfCows 100000

ifstream fin ("convention2.in");
ofstream fout ("convention2.out");

struct Cow
{
    int arrivingTime;
    int eatingDuration;
    int seniority;

    bool operator< (const Cow& c) const
    {
        return seniority > c.seniority;
    }
};

struct Event
{
    int time;
    int cow;
    int type;

    bool operator< (const Event& e) const
    {
        if (time != e.time)
        {
            return time > e.time;
        }
        return type > e.type;
    }
};

Cow cows[MaxNumberOfCows];
int numberOfCows;

void Input()
{
    Read >> numberOfCows;

    for (int i = 0; i < numberOfCows; i++)
    {
        Read >> cows[i].arrivingTime >> cows[i].eatingDuration;
        cows[i].seniority = i;
    }
}

int GetMaxWaitTime()
{
    priority_queue<Event> events;
    priority_queue<Cow> waitingCows;

    for (int i = 0; i < numberOfCows; i++)
    {
        events.push( {cows[i].arrivingTime, i, 0} );
    }

    int maxWaitTime = 0;
    int startedWaiting[MaxNumberOfCows];

    int currEatingCow = -1;
    int currEatingStart = -1;
    int currEatingEnd = -1;

    while (!events.empty())
    {
        Event currEvent = events.top();
        events.pop();

        if (currEvent.type == 0)
        {
            if (currEatingCow == -1)
            {
                waitingCows.push(cows[currEvent.cow]);
                startedWaiting[currEvent.cow] = currEvent.time;
                while (!events.empty() && events.top().time == currEvent.time)
                {
                    waitingCows.push(cows[events.top().cow]);
                    startedWaiting[events.top().cow] = currEvent.time;
                    events.pop();
                }

                currEatingCow = waitingCows.top().seniority;
                waitingCows.pop();
                currEatingStart = currEvent.time;
                currEatingEnd = currEatingStart + cows[currEatingCow].eatingDuration;
                events.push( {currEatingEnd, currEatingCow, 1} );
                maxWaitTime = max(maxWaitTime, currEatingStart - startedWaiting[currEatingCow]);
            }
            else
            {
                waitingCows.push(cows[currEvent.cow]);
                startedWaiting[currEvent.cow] = currEvent.time;
            }
        }
        else
        {
            currEatingCow = -1;
            currEatingStart = -1;
            currEatingEnd = -1;

            if (!waitingCows.empty())
            {
                currEatingCow = waitingCows.top().seniority;
                waitingCows.pop();
                currEatingStart = currEvent.time;
                currEatingEnd = currEatingStart + cows[currEatingCow].eatingDuration;
                events.push( {currEatingEnd, currEatingCow, 1} );
                maxWaitTime = max(maxWaitTime, currEatingStart - startedWaiting[currEatingCow]);
            }
        }
    }

    return maxWaitTime;
}

int main()
{
    Input();

    Write << GetMaxWaitTime() << endl;

    return 0;
}
