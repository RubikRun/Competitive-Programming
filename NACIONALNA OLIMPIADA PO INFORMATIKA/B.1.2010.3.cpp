//checked - 100%

#include <cstdio>
#include <algorithm>

using namespace std;

#define ChessBoardSize 8
#define PawnSymbol 'p'
#define QueenSymbol 'q'
#define EmptySymbol 'e'

void InitBoard(char board[][ChessBoardSize])
{
    for (int i = 0; i < ChessBoardSize; i++)
    {
        for (int j = 0; j < ChessBoardSize; j++)
        {
            board[i][j] = EmptySymbol;
        }
    }
}

void ReadBoard(char board[][ChessBoardSize])
{
    char input[2];

    int currX, currY, prevX = -1, prevY = -1, prevPrevX = -1, prevPrevY = -1;
    while(scanf("%s", input) == 1)
    {
        currX = input[0] - 'a';
        currY = input[1] - '1';

        board[currX][currY] = PawnSymbol;

        prevPrevX = prevX;
        prevPrevY = prevY;
        prevX = currX;
        prevY = currY;
    }
    board[prevX][prevY] = QueenSymbol;
    board[prevPrevX][prevPrevY] = QueenSymbol;
}

bool PawnInDanger(int x, int y, char board[][ChessBoardSize])
{
    int maxDistanceNeeded = max(x, max(ChessBoardSize - x, max(y, ChessBoardSize - y)));

    bool metPawn[8]; // metPawn[i] answers the question "Have I met a pawn in direction i?"
    for (int i = 0; i < 8; i++) metPawn[i] = false;

    for (int distance = 1; distance <= maxDistanceNeeded; distance++)
    {
        if (!metPawn[0] && x + distance < ChessBoardSize)
        {
            if (board[x + distance][y] == QueenSymbol)
            {
                return true;
            }
            if (board[x + distance][y] == PawnSymbol)
            {
                metPawn[0] = true;
            }
        }
        if (!metPawn[1] && x + distance < ChessBoardSize && y + distance < ChessBoardSize)
        {
            if (board[x + distance][y + distance] == QueenSymbol)
            {
                return true;
            }
            if (board[x + distance][y + distance] == PawnSymbol)
            {
                metPawn[1] = true;
            }
        }
        if (!metPawn[2] && y + distance < ChessBoardSize)
        {
            if (board[x][y + distance] == QueenSymbol)
            {
                return true;
            }
            if (board[x][y + distance] == PawnSymbol)
            {
                metPawn[2] = true;
            }
        }
        if (!metPawn[3] && x - distance >= 0 && y + distance < ChessBoardSize)
        {
            if (board[x - distance][y + distance] == QueenSymbol)
            {
                return true;
            }
            if (board[x - distance][y + distance] == PawnSymbol)
            {
                metPawn[3] = true;
            }
        }
        if (!metPawn[4] && x - distance >= 0)
        {
            if (board[x - distance][y] == QueenSymbol)
            {
                return true;
            }
            if (board[x - distance][y] == PawnSymbol)
            {
                metPawn[4] = true;
            }
        }
        if (!metPawn[5] && x - distance >= 0 && y - distance >= 0)
        {
            if (board[x - distance][y - distance] == QueenSymbol)
            {
                return true;
            }
            if (board[x - distance][y - distance] == PawnSymbol)
            {
                metPawn[5] = true;
            }
        }
        if (!metPawn[6] && y - distance >= 0)
        {
            if (board[x][y - distance] == QueenSymbol)
            {
                return true;
            }
            if (board[x][y - distance] == PawnSymbol)
            {
                metPawn[6] = true;
            }
        }
        if (!metPawn[7] && x + distance < ChessBoardSize && y - distance >= 0)
        {
            if (board[x + distance][y - distance] == QueenSymbol)
            {
                return true;
            }
            if (board[x + distance][y - distance] == PawnSymbol)
            {
                metPawn[7] = true;
            }
        }
    }

    return false;
}

int CountPawnsInDanger(char board[][ChessBoardSize])
{
    int numberOfPawnsInDanger = 0;

    for (int i = 0; i < ChessBoardSize; i++)
    {
        for (int j = 0; j < ChessBoardSize; j++)
        {
            if (board[i][j] == PawnSymbol && PawnInDanger(i, j, board))
            {
                numberOfPawnsInDanger++;
            }
        }
    }

    return numberOfPawnsInDanger;
}

int main()
{
    char board[ChessBoardSize][ChessBoardSize];
    InitBoard(board);
    ReadBoard(board);

    int numberOfPawnsInDanger = CountPawnsInDanger(board);
    printf("%d\n", numberOfPawnsInDanger);
    return 0;
}