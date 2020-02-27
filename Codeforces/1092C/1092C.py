n = int(input())

ps = []
for i in range(2 * n - 2):
    newString = input()
    ps.append(newString)

A = ''
B = ''
for i in ps:
    if len(i) == n - 1:
        if A == '':
            A = i
        else:
            B = i;
            break

AB = True
for i in range(n - 2):
    if B[i] != A[i + 1]:
        AB = False
        break

if AB:
    s = A[0] + B
else:
    s = B[0] + A

d = {}
for i in ps:
    if len(i) in d:
        if d[len(i)] == 'S':
            print('P', end='')
        else:
            print('S', end='')
        continue
    if s.endswith(i):
        print('S', end = '')
        d[len(i)] = 'S'
    else:
        print('P', end = '')
        d[len(i)] = 'P'

print()
