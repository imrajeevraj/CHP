import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    qrTNum = int(data[0])
    idx = 1
    out = []

    for _ in range(qrTNum):
        n = int(data[idx])
        s = data[idx + 1]
        idx += 2

        if s[0] == "0" or "00" in s:
            out.append("-1")
            continue

        low = 1
        high = n + 1
        ans = -1

        while low <= high:
            mid = (low + high) // 2

            L = 0
            R = 0
            possible = True

            for ch in s:
                if L == R:
                    x = L
                    if ch == "+":
                        l1, r1 = max(1, x - mid), x - 1
                        l2, r2 = max(1, x + 1), x + mid

                        valid1 = l1 <= r1
                        valid2 = l2 <= r2

                        if valid1 and valid2:
                            nL = min(l1, l2)
                            nR = max(r1, r2)
                        elif valid1:
                            nL, nR = l1, r1
                        elif valid2:
                            nL, nR = l2, r2
                        else:
                            possible = False
                            break
                    elif ch == "-":
                        l1, r1 = x - mid, min(-1, x - 1)
                        l2, r2 = x + 1, min(-1, x + mid)

                        valid1 = l1 <= r1
                        valid2 = l2 <= r2

                        if valid1 and valid2:
                            nL = min(l1, l2)
                            nR = max(r1, r2)
                        elif valid1:
                            nL, nR = l1, r1
                        elif valid2:
                            nL, nR = l2, r2
                        else:
                            possible = False
                            break
                    else:
                        if x != 0 and abs(x) <= mid:
                            nL, nR = 0, 0
                        else:
                            possible = False
                            break
                else:
                    rawL = L - mid
                    rawR = R + mid
                    if ch == "+":
                        nL = max(1, rawL)
                        nR = rawR
                    elif ch == "-":
                        nL = rawL
                        nR = min(-1, rawR)
                    else:
                        if rawL <= 0 <= rawR:
                            nL, nR = 0, 0
                        else:
                            possible = False
                            break

                if nL > nR:
                    possible = False
                    break

                L, R = nL, nR

            if possible:
                ans = mid
                high = mid - 1
            else:
                low = mid + 1

        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()