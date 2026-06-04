t = int(input())

for _ in range(t):
    n = int(input())

    ans = 0
    i = 1

    while n % i == 0:
        ans += 1
        i += 1

    print(ans)