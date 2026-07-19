import random
import time

MOD = 998244353
P1 = 1000000007
P2 = 1000000009

random.seed(int(time.time() * 1000000))


def power(base, exp):
    result = 1
    base %= MOD

    while exp > 0:
        if exp & 1:
            result = result * base % MOD
        base = base * base % MOD
        exp >>= 1

    return result


def add(a, b):
    x = a[0] + b[0]
    y = a[1] + b[1]

    if x >= P1:
        x -= P1
    if y >= P2:
        y -= P2

    return (x, y)


def mul(a, b):
    return (
        (a[0] * b[0]) % P1,
        (a[1] * b[1]) % P2
    )


def solve():
    n, m = map(int, input().split())

    grid = [input().strip() for _ in range(n)]

    total = n * m

    W_r = []
    W_d = []

    for _ in range(total):
        W_r.append((
            random.randint(1, P1 - 1),
            random.randint(1, P2 - 1)
        ))

        W_d.append((
            random.randint(1, P1 - 1),
            random.randint(1, P2 - 1)
        ))

    A = [(0, 0)] * total

    if grid[0][0] == '1':
        A[0] = (1, 1)

    for i in range(n):
        for j in range(m):

            if grid[i][j] == '0':
                continue

            u = i * m + j

            cur = A[u]

            if i > 0 and grid[i - 1][j] == '1':
                up = (i - 1) * m + j
                cur = add(cur, mul(A[up], W_d[up]))

            if j > 0 and grid[i][j - 1] == '1':
                left = i * m + j - 1
                cur = add(cur, mul(A[left], W_r[left]))

            A[u] = cur

    B = [(0, 0)] * total

    if grid[n - 1][m - 1] == '1':
        B[total - 1] = (1, 1)

    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):

            if grid[i][j] == '0':
                continue

            u = i * m + j

            cur = B[u]

            if i + 1 < n and grid[i + 1][j] == '1':
                down = (i + 1) * m + j
                cur = add(cur, mul(B[down], W_d[u]))

            if j + 1 < m and grid[i][j + 1] == '1':
                right = i * m + j + 1
                cur = add(cur, mul(B[right], W_r[u]))

            B[u] = cur

    hashes = []
    empty = 0

    for i in range(total):
        h = mul(A[i], B[i])

        if h == (0, 0):
            empty += 1
        else:
            hashes.append(h)

    hashes.sort()

    answer = (power(2, empty) - 1) % MOD

    i = 0

    while i < len(hashes):

        j = i

        while j < len(hashes) and hashes[j] == hashes[i]:
            j += 1

        freq = j - i

        answer = (answer + power(2, freq) - 1) % MOD

        i = j

    print(answer % MOD)


t = int(input())

for _ in range(t):
    solve()