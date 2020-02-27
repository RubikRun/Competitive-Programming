/*
ID: borisd22
TASK: spin
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;
#define Read fin
#define Write fout
#define NumberOfWheels 5

ifstream fin ("spin.in");
ofstream fout ("spin.out");

struct Wedge
{
    int startAngle;
    int area;
};

struct Wheel
{
    int angle;
    int speed;
    vector<Wedge> wedges;
};

Wheel wheels[NumberOfWheels];

bool InWedge(int angle, Wedge wedge)
{
    if (wedge.startAngle + wedge.area < 360)
    {
        return (angle >= wedge.startAngle && angle <= wedge.startAngle + wedge.area);
    }
    else
    {
        return (angle >= wedge.startAngle || angle <= (wedge.startAngle + wedge.area) % 360);
    }
}

void Input()
{
    for (int i = 0; i < NumberOfWheels; i++)
    {
        wheels[i].angle = 0;

        Read >> wheels[i].speed;

        int numberOfWedges;
        Read >> numberOfWedges;
        for (int j = 0; j < numberOfWedges; j++)
        {
            wheels[i].wedges.push_back({-1, -1});
            Read >> wheels[i].wedges.back().startAngle >> wheels[i].wedges.back().area;
        }
    }
}

void TimePass()
{
    for (int i = 0; i < NumberOfWheels; i++)
    {
        wheels[i].angle = (wheels[i].angle + wheels[i].speed) % 360;
    }
}

bool BeamCanPass()
{
    for (int i = 0; i < 360; i++)
    {
        bool angleIsOpen = true;
        for (int j = 0; j < NumberOfWheels; j++)
        {
            bool holeFound = false;
            for (int w = 0; w < wheels[j].wedges.size(); w++)
            {
                if (InWedge((i + 360 - wheels[j].angle) % 360, wheels[j].wedges[w]))
                {
                    holeFound = true;
                    break;
                }
            }
            if (!holeFound)
            {
                angleIsOpen = false;
                break;
            }
        }

        if (angleIsOpen)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    Input();

    for (int i = 0; i < 360; i++)
    {
        if (BeamCanPass())
        {
            Write << i << endl;
            return 0;
        }
        TimePass();
    }

    Write << "none" << endl;

    return 0;
}
