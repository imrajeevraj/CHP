t = int(input())

for _ in range(t):
    n = int(input())
    s = input()

    mx = 1
    cur = 1

    for i in range(1, n):
        if s[i] == s[i - 1]:
            cur += 1
        else:
            cur = 1

        mx = max(mx, cur)

    print(mx + 1)