import sys
from bisect import bisect_right

it = iter(map(int, sys.stdin.buffer.read().split()))
t = next(it)

out = []

for _ in range(t):
    n = next(it)
    m = next(it)
    k = next(it)

    size = n * m
    a = [0] * size
    row = [0] * n
    col = [0] * m

    for i in range(n):
        base = i * m
        s = 0
        for j in range(m):
            x = next(it)
            a[base + j] = x
            s += x
            col[j] += x
        row[i] = s

    need = [0] * size
    idx = 0
    for i in range(n):
        r = row[i]
        for j in range(m):
            need[idx] = r + col[j] - 3 * a[idx]
            idx += 1

    if n == 1 and m == 1:
        out.append("0" if need[0] <= 0 else "-1")
        continue

    srt = sorted(need)

    if n > 1 and m > 1:
        worst = srt[k - 1]
        step = n + m - 3
        out.append("0" if worst <= 0 else str((worst + step - 1) // step))
        continue

    length = size
    top = srt[-1]

    if length == 2:
        hi = max(0, top)
    else:
        hi = 0 if top <= 0 else (top + length - 3) // (length - 2)

    lo = 0

    while lo < hi:
        mid = (lo + hi) // 2
        base = mid * (length - 2)

        ok = bisect_right(srt, base) >= k

        if not ok:
            p = max(0, need[0] - base)
            if p <= mid:
                lim = base - p
                if bisect_right(srt, lim) + (need[0] > lim) >= k:
                    ok = True

        if not ok:
            q = max(0, need[-1] - base)
            if q <= mid:
                lim = base - q
                if bisect_right(srt, lim) + (need[-1] > lim) >= k:
                    ok = True

        if ok:
            hi = mid
        else:
            lo = mid + 1

    out.append(str(lo))

sys.stdout.write("\n".join(out))