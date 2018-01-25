#include <iostream>
#include <algorithm>
using namespace std;

struct vertical
{
    int y1, y2, x;
};

bool compFunc(vertical a, vertical b) { return a.x < b.x; }

int main()
{
    char input[12000];
    int i=0, dir=0, currX=0, currY=0, verCount=0, currNum=0, hs[6000], hsCount=0, inner=0, prevX;
    vertical verticals[6000], currVertical;

    cin>>input;
    while (input[i]!='\0')
    {
        if (input[i]=='+' || input[i]=='-' || input[i+1]=='\0')
        {
            if (input[i+1]=='\0')
            {
                currNum*=10;
                currNum+=input[i]-'0';
            }
            if (dir==0) currX+=currNum;
            else if (dir==2) currX-=currNum;
            else
            {
                if (dir==1)
                {
                    currVertical.y1=currY;
                    currVertical.y2=currY+currNum;
                    currY+=currNum;
                }
                else if (dir==3)
                {
                    currVertical.y1=currY-currNum;
                    currVertical.y2=currY;
                    currY-=currNum;
                }
                currVertical.x = currX;
                verticals[verCount++]=currVertical;

                hs[hsCount++]=currVertical.y1;
                hs[hsCount++]=currVertical.y2;
            }
            currNum=0;
            if (input[i]=='+') dir++;
            else if (input[i]=='-') dir--;
            if (dir==-1) dir=3;
            else if (dir==4) dir=0;
        }
        else
        {
            currNum*=10;
            currNum+=input[i]-'0';
        }
        i++;
    }

    sort(&verticals[0], &verticals[verCount], compFunc);
    sort(&hs[0], &hs[hsCount]);
    long area=0;

    for (int i=0; i<hsCount-1; i++)
    {
        if (hs[i+1]==hs[i]) continue;
        for (int j=0; j<verCount; j++)
        {
            if (verticals[j].y1<=hs[i] && verticals[j].y2>=hs[i+1])
            {
                if (inner==1)
                {
                    area += (hs[i+1]-hs[i]) * (verticals[j].x - prevX);
                    inner=0;
                }
                else
                {
                    inner=1;
                    prevX=verticals[j].x;
                }
            }
        }
    }
    cout<<area<<endl;
    return 0;
}