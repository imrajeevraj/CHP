t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))

    if n == 1:
        print(0)
        continue

    ans = max(
        max(a[i] - a[i + 1] for i in range(n - 1)),
        max(a[i] - a[0] for i in range(1, n)),
        max(a[-1] - a[i] for i in range(n - 1))
    )

    print(ans)