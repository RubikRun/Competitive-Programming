/*
ID: borisd22
TASK: castle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout ("castle.out");
ifstream fin ("castle.in");

#define MaxNumberOfRows 50
#define MaxNumberOfCols 50


struct Castle
{
    int numberOfRows, numberOfCols;
    int wall[MaxNumberOfRows][MaxNumberOfCols][4];
    int belongToRoom[MaxNumberOfRows][MaxNumberOfCols];
    vector<int> roomSizes;
};
#define InCastle(r, c, castle) (r >= 0 && r < castle.numberOfRows && c >= 0 && c < castle.numberOfCols)

Castle ReadCastle()
{
    Castle castle;

    fin >> castle.numberOfCols >> castle.numberOfRows;

    int wallNumber;
    for (int i = 0; i < castle.numberOfRows; i++)
    {
        for (int j = 0; j < castle.numberOfCols; j++)
        {
            fin >> wallNumber;

            castle.wall[i][j][0] = 0;
            castle.wall[i][j][1] = 0;
            castle.wall[i][j][2] = 0;
            castle.wall[i][j][3] = 0;

            int potentialAddend = 8;
            int wallIndex = 3;

            while (wallNumber != 0)
            {
                while (wallNumber - potentialAddend < 0)
                {
                    potentialAddend /= 2;
                    wallIndex--;
                }
                castle.wall[i][j][wallIndex] = 1;
                wallNumber -= potentialAddend;
            }
        }
    }

    return castle;
}

void VisitRoom(Castle& castle, int row, int col, int& roomSize, int& numberOfRooms)
{
    castle.belongToRoom[row][col] = numberOfRooms;
    roomSize++;
    if (InCastle(row, col - 1, castle) && !castle.wall[row][col][0] && castle.belongToRoom[row][col - 1] == -1)
    {
        VisitRoom(castle, row, col - 1, roomSize, numberOfRooms);
    }
    if (InCastle(row - 1, col, castle) && !castle.wall[row][col][1] && castle.belongToRoom[row - 1][col] == -1)
    {
        VisitRoom(castle, row - 1, col, roomSize, numberOfRooms);
    }
    if (InCastle(row, col + 1, castle) && !castle.wall[row][col][2] && castle.belongToRoom[row][col + 1] == -1)
    {
        VisitRoom(castle, row, col + 1, roomSize, numberOfRooms);
    }
    if (InCastle(row + 1, col, castle) && !castle.wall[row][col][3] && castle.belongToRoom[row + 1][col] == -1)
    {
        VisitRoom(castle, row + 1, col, roomSize, numberOfRooms);
    }
}

int GetSizeOfLargestRoom(Castle& castle, int& numberOfRooms)
{
    for (int i = 0; i < castle.numberOfRows; i++)
    {
        for (int j = 0; j < castle.numberOfCols; j++)
        {
            castle.belongToRoom[i][j] = -1;
        }
    }

    int sizeOfLargestRoom = 0, sizeOfCurrentRoom;
    numberOfRooms = 0;
    for (int i = 0; i < castle.numberOfRows; i++)
    {
        for (int j = 0; j < castle.numberOfCols; j++)
        {
            if (castle.belongToRoom[i][j] == -1)
            {
                sizeOfCurrentRoom = 0;
                VisitRoom(castle, i, j, sizeOfCurrentRoom, numberOfRooms);
                castle.roomSizes.push_back(sizeOfCurrentRoom);
                sizeOfLargestRoom = max(sizeOfLargestRoom, sizeOfCurrentRoom);
                numberOfRooms++;
            }
        }
    }

    return sizeOfLargestRoom;
}

int GetLargestJoinedRoomsSize(Castle& castle, int& answerRow, int& answerCol, char& answerDir)
{
    int largestJoinedRoomsSize = 0;

    int currentJoinedRoomsSize;
    for (int j = 0; j < castle.numberOfCols; j++)
    {
        for (int i = castle.numberOfRows - 1; i >= 0; i--)
        {
            for (int deltaX = 0; deltaX <= 1; deltaX++)
            {
                for (int deltaY = -1; deltaY <= 0; deltaY++)
                {
                    if (deltaX + deltaY == 0)
                    {
                        continue;
                    }
                    if (InCastle(i + deltaY, j + deltaX, castle) && castle.belongToRoom[i][j] != castle.belongToRoom[i + deltaY][j + deltaX])
                    {
                        currentJoinedRoomsSize = castle.roomSizes[castle.belongToRoom[i][j]] + castle.roomSizes[castle.belongToRoom[i + deltaY][j + deltaX]];

                        if (currentJoinedRoomsSize > largestJoinedRoomsSize)
                        {
                            largestJoinedRoomsSize = currentJoinedRoomsSize;
                            answerRow = i;
                            answerCol = j;
                            if (deltaX == 1)
                            {
                                answerDir = 'E';
                            }
                            else
                            {
                                answerDir = 'N';
                            }
                        }
                    }
                }
            }
        }
    }

    return largestJoinedRoomsSize;
}

int main()
{
    Castle castle = ReadCastle();

    int numberOfRooms;
    int sizeOfLargestRoom = GetSizeOfLargestRoom(castle, numberOfRooms);
    int joinedRow, joinedCol;
    char joinedDir;
    int largestJoinedRoomsSize = GetLargestJoinedRoomsSize(castle, joinedRow, joinedCol, joinedDir);

    fout << numberOfRooms << endl;
    fout << sizeOfLargestRoom << endl;
    fout << largestJoinedRoomsSize << endl;
    fout << joinedRow + 1 << " " << joinedCol + 1 << " " << joinedDir << endl;

    return 0;
}