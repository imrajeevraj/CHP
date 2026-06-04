import math

t = int(input())

for _ in range(t):
    n = int(input())
    m = list(map(int, input().split()))
    res = False
    for i in range(n):
        for j in range(i+1, n):
            if math.gcd(m[i], m[j]) <= 2:
                res = True
                break
        if res:
            break

    print("Yes" if res else "No")