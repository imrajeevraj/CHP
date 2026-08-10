import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))

    pref = [0] * (n + 1)
    for i in range(n):
        pref[i + 1] = pref[i] + a[i]

    ans = 0

    for k in range(1, n + 1):
        if n % k != 0:
            continue

        mn = float('inf')
        mx = 0

        for i in range(0, n, k):
            s = pref[i + k] - pref[i]
            mn = min(mn, s)
            mx = max(mx, s)

        ans = max(ans, mx - mn)

    print(ans)