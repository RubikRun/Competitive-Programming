#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Triangle
{
    int a, b, c;
    bool operator<(const Triangle& x)
    {
        if (a == x.a)
        {
            if (b == x.b)
            {
                return (c < x.c);
            }
            return (b < x.b);
        }
        return (a < x.a);
    }
};

int main()
{
    int P;
    cin >> P;
    double R;
    cin >> R;

    vector<Triangle> triForce;
    for (int a = 1; a <= P - 2; a++)
    {
        for (int b = a; a + b <= P - 1; b++)
        {
            for (int c = b; a + b + c <= P; c++)
            {
                if (R * R * P * (P - a) * (P - b) * (P - c) == a * a * b * b * c * c)
                {
                    int sides[3] = {a, b, c};
                    do
                    {
                        triForce.push_back({sides[0], sides[1], sides[2]});
                    } while (next_permutation(sides, sides + 3));
                }
            }
        }
    }
    sort(triForce.begin(), triForce.end());

    for (int i = 0; i < triForce.size(); i++)
    {
        cout << triForce[i].a << "." << triForce[i].b << "." << triForce[i].c << endl;
    }

    return 0;
}