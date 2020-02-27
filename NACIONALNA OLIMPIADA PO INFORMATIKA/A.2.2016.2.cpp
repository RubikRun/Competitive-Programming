//checked - 100%

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
#define MaxNumberOfCircles 10000
#define MaxNumberOfPoints 10
#define MaxNumberOfHits 10000

struct Point
{
	int x;
	int y;
};

struct Circle
{
	Point center;
	int radius;
};

Circle circles[MaxNumberOfCircles];
int numberOfCircles;

Point points[MaxNumberOfPoints];
int numberOfPoints;

int hits[MaxNumberOfHits];
int numberOfHits;

int radiusNeeded[MaxNumberOfPoints][MaxNumberOfCircles];

double GetDistance(Point& a, Point& b)
{
        return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}

void FillRadiusNeeded()
{
        for (int i = 0; i < numberOfPoints; i++)
        {
                for (int j = 0; j < numberOfCircles; j++)
                {
                        radiusNeeded[i][j] = ceil(GetDistance(points[i], circles[j].center) + circles[j].radius);
                }

		sort(radiusNeeded[i], radiusNeeded[i] + numberOfCircles);
        }


}

void Input()
{
	scanf("%d %d %d", &numberOfCircles, &numberOfPoints, &numberOfHits);

	for (int i = 0; i < numberOfCircles; i++)
	{
		scanf("%d %d %d", &circles[i].center.x, &circles[i].center.y, &circles[i].radius);
	}

	for (int i = 0; i < numberOfPoints; i++)
	{
		scanf("%d %d", &points[i].x, &points[i].y);
	}

	for (int i = 0; i < numberOfHits; i++)
	{
		scanf("%d", &hits[i]);
	}

	FillRadiusNeeded();
}

int GetNumberOfCirclesInside(int pointIndex, int radius)
{
	if (radius < radiusNeeded[pointIndex][0])
	{
		return 0;
	}
	if (radius >= radiusNeeded[pointIndex][numberOfCircles - 1])
	{
		return numberOfCircles;
	}

	int first = 0, last = numberOfCircles;
	while (first <= last)
	{
		int middle = (first + last) / 2;

		if (radiusNeeded[pointIndex][middle] <= radius && radiusNeeded[pointIndex][middle + 1] > radius)
		{
			return middle + 1;
		}
		
		if (radiusNeeded[pointIndex][middle] > radius)
		{
			last = middle - 1;
		}
		else
		{
			first = middle + 1;
		}
	}

	return 0;
}

int GetScoreForRadius(int radius)
{
	int score = 0;

	for (int i = 0; i < numberOfPoints; i++)
	{
		score += GetNumberOfCirclesInside(i, radius);
	}

	return score;
}

int GetTotalScore()
{
	int totalScore = 0;

	int prevScore = -1;
	int currScore;
	for (int i = 0; i < numberOfHits; i++)
	{
		if (prevScore % 2 == 0)
		{
			currScore = GetScoreForRadius(hits[i] * 2);
			totalScore += currScore;
		}
		else
		{
			currScore = GetScoreForRadius(hits[i]);
			totalScore += currScore;
		}

		prevScore = currScore;
	}

	return totalScore;
}

int main()
{
	Input();

	printf("%d\n", GetTotalScore());

	return 0;
}
