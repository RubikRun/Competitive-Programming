//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MaxNumberOfParticles 400000

struct Particle
{
	int position;
	int speed;

	bool operator< (const Particle& p) const
	{
		if (position * speed == p.position * p.speed)
		{
			return (position < p.position);
		}
		return (position * speed < p.position * p.speed);
	}
};

int numberOfParticles;

Particle xParticles[MaxNumberOfParticles];
Particle yParticles[MaxNumberOfParticles];

void Input()
{
	scanf("%d", &numberOfParticles);

	for (int i = 0; i < numberOfParticles; i++)
	{
		scanf("%d %d", &xParticles[i].position, &xParticles[i].speed);
	}
		for (int i = 0; i < numberOfParticles; i++)
	{
		scanf("%d %d", &yParticles[i].position, &yParticles[i].speed);
	}
}

void SortParticles()
{
	sort(xParticles, xParticles + numberOfParticles);
	sort(yParticles, yParticles + numberOfParticles);
}

int GetEnergy()
{
	int energy = 0;

	int xPointer = 0, yPointer = 0;
	while (xPointer < numberOfParticles && yPointer < numberOfParticles)
	{
		int xProduct = xParticles[xPointer].position * xParticles[xPointer].speed;
		int yProduct = yParticles[yPointer].position * yParticles[yPointer].speed;

		if (xProduct == yProduct)
		{
			energy++;
			xPointer++;
			yPointer++;
		}
		else if (xProduct < yProduct)
		{
			xPointer++;
		}
		else
		{
			yPointer++;
		}
	}

	return energy;
}

int main()
{
	Input();

	SortParticles();
	printf("%d\n", GetEnergy());

	return 0;
}