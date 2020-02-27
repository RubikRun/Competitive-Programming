n = int(input())

row = 0
pattern = ''
for k in [4, 3, 2, 1]:
    for i in range(n):
        if i%4 == k%4:
            pattern += '#'
        else:
            pattern += '.'
    pattern += '\n'

rowsLeft = n + n//2
while rowsLeft >= 4:
    print(pattern, end='')
    rowsLeft -= 4
print(pattern[:rowsLeft * (n + 1)])