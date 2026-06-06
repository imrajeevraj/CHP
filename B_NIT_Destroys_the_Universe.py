t = int(input())

for _ in range(t):
    n = int(input())
    num = list(map(int, input().split()))

    x = True
    count = 0

    for i in range(n):
        if num[i] == 0:
            x = True
        elif x:
            count += 1
            x = False

    print(min(count, 2))