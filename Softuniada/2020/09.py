def DoDP(x):
    dp = [0] * 1000
    dp[0] = 0
    dp[1] = 1
    for i in range(2, x + 1):
        dp[i] = 10000
        for coinValue in coinValues:
            if i - coinValue >= 0:
                dp[i] = min(dp[i], dp[i - coinValue] + 1)
    return dp[x]

def SolveForEvenLen(n):
    coinCount = 0
    for i in range(0, len(n), 2):
        coinCount += DoDP(int(n[i:i+2]))
    return coinCount

coinValues = [1, 10, 25]

n = input()

coinCount = 0

if len(n) == 1:
    coinCount = int(n)
elif len(n) % 2 == 0:
    coinCount = SolveForEvenLen(n)
else:
    coinCount = SolveForEvenLen(n[:-3]) + DoDP(n[-3:])

print(coinCount)