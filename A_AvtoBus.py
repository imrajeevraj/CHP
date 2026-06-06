t = int(input())

for _ in range(t):
    n = int(input())

    if n % 2 or n < 4:
        print(-1)
    else:
        print((n + 5) // 6, n // 4)