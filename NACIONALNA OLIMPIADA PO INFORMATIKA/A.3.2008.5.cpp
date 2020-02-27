//checked - 30%

#include <cstdio>
#include <algorithm>

using namespace std;
#define MAXN 1000

int arr[MAXN * MAXN];
int length[MAXN * MAXN];
int minEnd[MAXN * MAXN + 1];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n * n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int maxLength;

    length[0] = 1;
    minEnd[1] = arr[0];
    maxLength = 1;

    for (int i = 1; i < n * n; i++)
    {
        if (arr[i] < minEnd[1] && arr[i] % n <= minEnd[1] % n)
        {
            minEnd[1] = arr[i];
            length[i] = 1;
        }
        else if (arr[i] > minEnd[maxLength] && arr[i] % n >= minEnd[maxLength] % n)
        {
            length[i] = maxLength + 1;
            maxLength++;
            minEnd[maxLength] = arr[i];
        }
        else
        {
            int k;
            int first = 1, last = maxLength - 1;

            while (first <= last)
            {
                k = (first + last) / 2;

                if (arr[i] > minEnd[k] && arr[i] % n >= minEnd[k] % n && arr[i] < minEnd[k + 1] && arr[i] % n <= minEnd[k + 1] % n)
                {
                    break;
                }

                if (arr[i] < minEnd[k] && arr[i] % n <= minEnd[k] % n)
                {
                    last = k - 1;
                }
                else
                {
                    first = k + 1;
                }
            }

            length[i] = k + 1;
            if (arr[i] < minEnd[k + 1] && arr[i] % n <= minEnd[k + 1] % n)
            {
                minEnd[k + 1] = arr[i];
            }
        }
    }

    printf("%d\n", maxLength);

    return 0;
}
