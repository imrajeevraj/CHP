import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    x = list(map(int, input().split()))

    # Smallest x processed so far
    mn = 31

    for k in x:

        # Larger/equal x cannot affect the array anymore
        if k >= mn:
            continue

        div = 1 << k       # 2^k
        add = 1 << (k - 1) # 2^(k-1)

        for i in range(n):
            if a[i] % div == 0:
                a[i] += add

        mn = k

    print(*a)