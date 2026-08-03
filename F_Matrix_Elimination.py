from bisect import bisect_right

t = int(input())

for _ in range(t):
    n, m, k = map(int, input().split())

    a = [0] * (n * m)
    row = [0] * n
    col = [0] * m

    for i in range(n):
        arr = list(map(int, input().split()))
        for j in range(m):
            x = arr[j]
            a[i * m + j] = x
            row[i] += x
            col[j] += x

    need = [0] * (n * m)
    for i in range(n):
        for j in range(m):
            need[i * m + j] = row[i] + col[j] - 3 * a[i * m + j]

    if n == 1 and m == 1:
        print(0 if need[0] <= 0 else -1)
        continue

    srt = sorted(need)

    if n > 1 and m > 1:
        worst = srt[k - 1]
        step = n + m - 3
        if worst <= 0:
            print(0)
        else:
            print((worst + step - 1) // step)
        continue

    length = n * m
    top = srt[-1]

    if length == 2:
        hi = max(0, top)
    else:
        hi = 0 if top <= 0 else (top + length - 3) // (length - 2)

    def cnt(x):
        return bisect_right(srt, x)

    def good(T):
        base = T * (length - 2)

        if cnt(base) >= k:
            return True

        p = max(0, need[0] - base)
        if p <= T:
            lim = base - p
            if cnt(lim) + (1 if need[0] > lim else 0) >= k:
                return True

        q = max(0, need[length - 1] - base)
        if q <= T:
            lim = base - q
            if cnt(lim) + (1 if need[length - 1] > lim else 0) >= k:
                return True

        return False

    lo = 0
    while lo < hi:
        mid = (lo + hi) // 2
        if good(mid):
            hi = mid
        else:
            lo = mid + 1

    print(lo)