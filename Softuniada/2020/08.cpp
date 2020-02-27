#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 6

struct Stick
{
    int w, h;
    bool operator<(const Stick& s)
    {
        if (w == s.w)
        {
            return (h < s.h);
        }
        return (w < s.w);
    }
};

int perm[MAXN];
int permCount;
Stick sticks[MAXN * 2];
int sticksCount;
bool used[MAXN * 2];

void CountPermute(int x)
{
    if (x == sticksCount)
    {
        permCount++;
    }
    
    Stick sticksPut[MAXN * 2];
    int sticksPutCount = 0;
    for (int i = 0; i < sticksCount * 2; i++)
    {
        if (!used[i])
        {
            bool put = false;
            for (int j = 0; j < sticksPutCount; j++)
            {
                if (sticksPut[j].w == sticks[i].w && sticksPut[j].h == sticks[i].h)
                {
                    put = true;
                    break;
                }
            }
            if (put)
            {
                continue;
            }
            used[i] = true;
            int refl = -1;
            for (int j = 0; j < sticksCount; j++)
            {
                if (!used[j] && sticks[j].w == sticks[i].h && sticks[i].h == sticks[j].w)
                {
                    refl = j;
                    break;
                }
            }
            sticksPut[sticksPutCount++] = sticks[i];
            used[refl] = true;
            perm[x] = i;

            CountPermute(x + 1);

            used[i] = false;
            used[refl] = false;
        }
    }
}

void PrintPermute(int x)
{
    if (x == sticksCount)
    {
        for (int i = 0; i < sticksCount; i++)
        {
            cout << sticks[perm[i]].w << " " << sticks[perm[i]].h << "...";
        }
        cout << endl;
    }
    
    Stick sticksPut[MAXN * 2];
    int sticksPutCount = 0;
    for (int i = 0; i < sticksCount * 2; i++)
    {
        if (!used[i])
        {
            bool put = false;
            for (int j = 0; j < sticksPutCount; j++)
            {
                if (sticksPut[j].w == sticks[i].w && sticksPut[j].h == sticks[i].h)
                {
                    put = true;
                    break;
                }
            }
            if (put)
            {
                continue;
            }
            used[i] = true;
            int refl = -1;
            for (int j = 0; j < sticksCount; j++)
            {
                if (!used[j] && sticks[j].w == sticks[i].h && sticks[i].h == sticks[j].w)
                {
                    refl = j;
                    break;
                }
            }
            sticksPut[sticksPutCount++] = sticks[i];
            used[refl] = true;
            perm[x] = i;

            PrintPermute(x + 1);

            used[i] = false;
            used[refl] = false;
        }
    }
}

int main()
{
    cin >> sticksCount;
    for (int i = 0; i < sticksCount; i++)
    {
        cin >> sticks[i * 2].w >> sticks[i * 2].h;
        sticks[i * 2 + 1].w = sticks[i * 2].h;
        sticks[i * 2 + 1].h = sticks[i * 2].w;
    }
    sort(sticks, sticks + sticksCount * 2);

    for (int i = 0; i < sticksCount * 2; i++)
    {
        used[i] = false;
    }
    permCount = 0;
    //CountPermute(0);
    PrintPermute(0);

    cout << permCount << endl;
    return 0;
}