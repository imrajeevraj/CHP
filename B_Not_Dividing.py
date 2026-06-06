t = int(input())

for _ in range(t):
    n = int(input())
    num = list(map(int, input().split()))

    for i in range(n):
        if num[i] == 1:
            num[i] = 2

    for i in range(n - 1):
        if num[i + 1] % num[i] == 0:
            num[i + 1] += 1

    print(*num)