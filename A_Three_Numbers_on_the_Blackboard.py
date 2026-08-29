import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    t = int(data[0])
    idx = 1
    results = []
    
    for _ in range(t):
        a = int(data[idx])
        b = int(data[idx + 1])
        c = int(data[idx + 2])
        idx += 3
        
        mn = min(a, b, c)
        mx = max(a, b, c)
        mid = a + b + c - mn - mx
        
        # If mx >= mid + mn, we can replace mx with mid + mn, achieving range mid.
        # Otherwise, the minimum range is mx - mn.
        results.append(str(min(mx - mn, mid)))
        
    print("\n".join(results))

if __name__ == '__main__':
    solve()
