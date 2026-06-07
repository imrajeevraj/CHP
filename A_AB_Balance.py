t = int(input())

for _ in range(t):
    s = input().strip()

    s = s[-1] + s[1:]

    print(s)