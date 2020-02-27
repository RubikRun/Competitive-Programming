//Works

#include <iostream>

using namespace std;

const int numberOfPlayers = 473;
const int lastMarble = 70904;

//The whole structure of the circle
//For each marble on the circle we keep its prev and its next marble
int nextMarbleOnCircle[lastMarble + 1];
int prevMarbleOnCircle[lastMarble + 1];

int nextMarbleToPut;
int currMarble;

int currPlayer;
int points[numberOfPlayers]; //points[i] is the number of points of player i

void InitGame()
{
    for (int i = 0; i <= lastMarble; i++)
    {
        nextMarbleOnCircle[i] = -1;
        prevMarbleOnCircle[i] = -1;
    }
    nextMarbleOnCircle[0] = 0;
    prevMarbleOnCircle[0] = 0;

    currMarble = 0;
    nextMarbleToPut = 1;

    currPlayer = 0;
    for (int i = 0; i < numberOfPlayers; i++)
    {
        points[i] = 0;
    }
}

//Inserts marble x between marble a and marble b
void InsertBetweenTwoMarbles(int x, int a, int b)
{
    if (nextMarbleOnCircle[a] != b)
    {
        return;
    }

    nextMarbleOnCircle[a] = x;
    prevMarbleOnCircle[b] = x;
    nextMarbleOnCircle[x] = b;
    prevMarbleOnCircle[x] = a;
}

//Removes marble x from the circle
void RemoveFromCircle(int x)
{
    //Circle would be like ...axb...
    int a = prevMarbleOnCircle[x];
    int b = nextMarbleOnCircle[x];

    nextMarbleOnCircle[a] = b;
    prevMarbleOnCircle[b] = a;
    nextMarbleOnCircle[x] = -1;
    prevMarbleOnCircle[x] = -1;
}

void DoTurn()
{
    if (nextMarbleToPut % 23 == 0)
    {
        points[currPlayer] += nextMarbleToPut;
        int x = currMarble;
        for (int i = 0; i < 7; i++) x = prevMarbleOnCircle[x];
        currMarble = nextMarbleOnCircle[x];
        points[currPlayer] += x;
        RemoveFromCircle(x);
    }
    else
    {
        int a = nextMarbleOnCircle[currMarble];
        int b = nextMarbleOnCircle[a];
        InsertBetweenTwoMarbles(nextMarbleToPut, a, b);
        currMarble = nextMarbleToPut;
    }

    currPlayer = (currPlayer + 1) % numberOfPlayers;
    nextMarbleToPut++;
}

int main()
{
    InitGame();

    while (nextMarbleToPut <= lastMarble)
    {
        DoTurn();
    }

    int maxPoints = 0;
    for (int i = 0; i < numberOfPlayers; i++)
    {
        maxPoints = max(maxPoints, points[i]);
    }

    cout << maxPoints << endl;

    return 0;
}
