import sys
import math

def solve():
    it = iter(sys.stdin.read().split())
    t = int(next(it))
    out_lines = []

    for _ in range(t):
        n = int(next(it))
        a = [int(next(it)) for _ in range(n)]

        if n == 1:
            out_lines.append("0")
            continue

        ans = 0
        prev = []  # list of (gcd_value, count)

        for i in range(1, n):
            x = abs(a[i] - a[i - 1])

            cur = [(x, 1)]

            for g, cnt in prev:
                ng = math.gcd(g, x)
                if cur[-1][0] == ng:
                    cur[-1] = (ng, cur[-1][1] + cnt)
                else:
                    cur.append((ng, cnt))

            for g, cnt in cur:
                ans += g * cnt

            prev = cur

        out_lines.append(str(ans))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()