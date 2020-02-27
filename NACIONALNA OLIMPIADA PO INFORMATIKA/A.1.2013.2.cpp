//checked - 100%

#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x;
    int y;
};

bool ArePerpendicular(Point& A, Point& B, Point& C, Point& D)
{
    return (A.x - B.x) * (C.x - D.x) + (A.y - B.y) * (C.y - D.y) == 0;
}

int main()
{
    Point A;
    cin >> A.x >> A.y;
    Point B;
    cin >> B.x >> B.y;

    int width, height;
    cin >> width >> height;

    Point C, D;
    int numberOfSegments = 0;
    vector<int> differentSums;
    for (C.x = 1; C.x < width; C.x++)
    {
        for (C.y = 1; C.y < height; C.y++)
        {
            for (D.x = C.x; D.x < width; D.x++)
            {
                for (D.y = 1; D.y < height; D.y++)
                {
                    if (D.x == C.x && D.y <= C.y)
                    {
                        continue;
                    }
                    if (ArePerpendicular(A, B, C, D))
                    {
                        numberOfSegments++;

                        int sum = abs(C.x - D.x) + abs(C.y - D.y);
                        bool newSum = true;
                        for (int i = 0; i < differentSums.size(); i++)
                        {
                            if (differentSums[i] == sum)
                            {
                                newSum = false;
                                break;
                            }
                        }

                        if (newSum)
                        {
                            differentSums.push_back(sum);
                        }
                    }
                }
            }
        }
    }

    cout << numberOfSegments << " " << differentSums.size() << endl;

    return 0;
}