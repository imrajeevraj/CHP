import sys
sys.setrecursionlimit(1 << 25)
input = sys.stdin.readline

MOD = 10**9 + 7
MAXA = 500000

# Smallest prime factor sieve
spf = list(range(MAXA + 1))
for i in range(2, int(MAXA**0.5) + 1):
    if spf[i] == i:
        step = i
        start = i * i
        for j in range(start, MAXA + 1, step):
            if spf[j] == j:
                spf[j] = i

def distinct_primes(x: int):
    """Return distinct prime factors of x using spf."""
    res = []
    while x > 1:
        p = spf[x]
        res.append(p)
        while x % p == 0:
            x //= p
    return res

t = int(input())
for _ in range(t):
    n, x = map(int, input().split())  # x == 1 in F1
    a = list(map(int, input().split()))

    # Group by radical (product of distinct primes)
    cnt = {}
    for v in a:
        y = v
        rad = 1
        while y > 1:
            p = spf[y]
            rad *= p
            while y % p == 0:
                y //= p
        cnt[rad] = cnt.get(rad, 0) + 1

    ans = 1

    for rad, c in cnt.items():
        # primes in this group's kernel
        primes = distinct_primes(rad)
        k = len(primes)
        # each prime may appear in at most one chosen divisor among this group
        M = 1 << k

        # dp[mask] = ways for processed voters in this group,
        # mask tells which primes are already used
        f = [0] * M
        nf = [0] * M
        f[0] = 1

        for _rep in range(c):
            # transition for each voter of this group
            for i in range(M):
                nf[i] = 0
            for mask in range(M):
                val = f[mask]
                if not val:
                    continue
                free_mask = ((M - 1) ^ mask)
                sub = free_mask
                # choose any subset of free primes as the primes in this voter's divisor
                while True:
                    nmask = mask | sub
                    nf[nmask] += val
                    if nf[nmask] >= MOD:
                        nf[nmask] -= MOD
                    if sub == 0:
                        break
                    sub = (sub - 1) & free_mask
            f, nf = nf, f

        ways = sum(f) % MOD
        ans = ans * ways % MOD

    print(ans % MOD)