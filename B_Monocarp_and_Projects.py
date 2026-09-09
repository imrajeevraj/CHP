t = int(input())

for _ in range(t):
    x, y, k = map(int, input().split())

    d = y - x
    ans = 0


    special = min(k, d - x + 1)

    for i in range(special):
        employees = x + i
        ans += d % employees

    
    remaining = k - special
    ans += remaining * d

    print(ans)