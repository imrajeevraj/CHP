import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    prefix = 0          # Sum of first-time rewards
    best_repeat = 0     # Maximum repeat reward seen so far
    ans = 0

    # We cannot unlock more than k quests
    for i in range(min(n, k)):
        prefix += a[i]
        best_repeat = max(best_repeat, b[i])

        remaining = k - (i + 1)

        # Finish remaining completions on the best repeatable quest
        ans = max(ans, prefix + remaining * best_repeat)

    print(ans)