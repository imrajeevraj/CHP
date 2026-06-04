import sys

input = sys.stdin.readline

def moves(x, y, a, b):
    res = set()
    res.add((x + a, y + b))
    res.add((x + a, y - b))
    res.add((x - a, y + b))
    res.add((x - a, y - b))
    res.add((x + b, y + a))
    res.add((x + b, y - a))
    res.add((x - b, y + a))
    res.add((x - b, y - a))
    return res

t = int(input())
for _ in range(t):
    a, b = map(int, input().split())
    xk, yk = map(int, input().split())
    xq, yq = map(int, input().split())

    king_moves = moves(xk, yk, a, b)
    queen_moves = moves(xq, yq, a, b)

    ans = len(king_moves & queen_moves)
    print(ans)