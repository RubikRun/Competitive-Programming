#include <cstdio>
#include <vector>
using namespace std;

#define MaxNumberOfBits 60

struct BinaryNumber
{
    int digits[MaxNumberOfBits];
    int numberOfDigits;
};

BinaryNumber GetBinaryNumber(long long decimalNumber)
{
    BinaryNumber binaryNumber;
    binaryNumber.numberOfDigits = 0;

    while (decimalNumber != 0)
    {
        binaryNumber.digits[binaryNumber.numberOfDigits++] = decimalNumber % 2;
        decimalNumber /= 2;
    }

    return binaryNumber;
}

int Belongs(BinaryNumber number)
{
    if (number.digits[0] == 0)
    {
        return 0;
    }

    int numberOfOnes = 0;
    for (int digitIndex = 0; digitIndex < number.numberOfDigits; digitIndex++)
    {
        if (number.digits[digitIndex] == 1)
        {
            numberOfOnes++;
        }
        else
        {
            if (numberOfOnes % 2 == 0)
            {
                return 0;
            }

            numberOfOnes = 0;
        }
    }

    return 1;
}

int main()
{
    long long firstNumber, secondNumber, thirdNumber;
    scanf("%lld%lld%lld", &firstNumber, &secondNumber, &thirdNumber);

    int firstBelongs = Belongs(GetBinaryNumber(firstNumber));
    int secondBelongs = Belongs(GetBinaryNumber(secondNumber));
    int thirdBelongs = Belongs(GetBinaryNumber(thirdNumber));

    printf("%d%d%d\n", firstBelongs, secondBelongs, thirdBelongs);

    return 0;
}