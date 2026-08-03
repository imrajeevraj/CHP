from bisect import bisect_right
import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, m, d = map(int, input().split())

    p = []
    prefix = [0] * (m + 1)
    candidates = [(0, 0)]

    for i in range(m):
        pos, reward = map(int, input().split())
        p.append(pos)
        prefix[i + 1] = prefix[i] + reward

        if pos < n:
            candidates.append((pos, prefix[i + 1]))

    total = prefix[m]

    def get(x):
        k = bisect_right(p, x % n)
        return (x // n) * total + prefix[k]

    ans = -10**30

    for x, rx in candidates:
        for y, ry in candidates:
            ans = max(ans, rx + ry - get(x + y + 1))

    print("YES" if ans > d else "NO")