from math import gcd

t = int(input())

for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))

    ans = 0
    for i in range(n):
        ans = gcd(ans, abs(p[i] - (i + 1)))

    print(ans)