import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    t = int(data[0])
    idx = 1
    out = []

    for _ in range(t):
        n = int(data[idx])
        idx += 1
        a = [int(x) for x in data[idx : idx + n]]
        idx += n

    
        cnt_easy = a.count(0)

        
        if cnt_easy < 2:
            out.append("-1")
        else:
    
            out.append(str(a[0] + a[-1]))

    print("\n".join(out))


if __name__ == "__main__":
    solve()