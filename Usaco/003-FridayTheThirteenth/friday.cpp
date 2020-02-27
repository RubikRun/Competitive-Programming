/*
ID: borisd22
TASK: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ofstream fout ("friday.out");
ifstream fin ("friday.in");

#define NumberOfDaysOfWeek 7

int YearIsLeap(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

int CountThirteens(int wantedDay, int years)
{
    int numberOfThirteens = 0;

    int monthsLens[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int currentDay = 5;
    int currentMonth = 0;
    int currentYear = 1900;
    int lastYear = currentYear + years;

    while (currentYear < lastYear)
    {
        monthsLens[1] = 28 + YearIsLeap(currentYear);
        while (currentMonth < 12)
        {
            if (currentDay == wantedDay)
            {
                numberOfThirteens++;
            }

            currentDay = (currentDay + monthsLens[currentMonth]) % 7;
            currentMonth++;
        }

        currentYear++;
        currentMonth = 0;
    }

    return numberOfThirteens;
}

int main()
{
    int years;
    fin >> years;

    int numbersOfThirteens[NumberOfDaysOfWeek];
    for (int day = 0; day < NumberOfDaysOfWeek; day++)
    {
        numbersOfThirteens[day] = CountThirteens(day, years);
    }

    for (int day = 5; day < 5 + NumberOfDaysOfWeek - 1; day++)
    {
        fout << numbersOfThirteens[day % NumberOfDaysOfWeek] << " ";
    }
    fout << numbersOfThirteens[4] << endl;

    return 0;
}