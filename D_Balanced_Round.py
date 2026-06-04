t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    x = list(map(int, input().split()))

    x.sort()

    cur = 1
    mx = 1

    for i in range(1, n):
        if x[i] - x[i-1] <= k:
            cur += 1
        else:
            cur = 1

        mx = max(mx, cur)

    print(n - mx)