import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    t = int(data[0])
    idx = 1
    MOD = 998244353
    results = []
    
    for _ in range(t):
        n = int(data[idx])
        s = data[idx + 1]
        idx += 2
        
        odd_chars = [s[i] for i in range(0, n, 2)]
        even_chars = [s[i] for i in range(1, n, 2)]
        
        # Check odd indices
        odd_ways = 0
        # Pattern 0: 0, 1, 0, 1, ...
        if all(ch == '?' or ch == str(i % 2) for i, ch in enumerate(odd_chars)):
            odd_ways += 1
        # Pattern 1: 1, 0, 1, 0, ...
        if all(ch == '?' or ch == str((i + 1) % 2) for i, ch in enumerate(odd_chars)):
            odd_ways += 1
            
        # Check even indices
        even_ways = 0
        # Pattern 0: 0, 1, 0, 1, ...
        if all(ch == '?' or ch == str(i % 2) for i, ch in enumerate(even_chars)):
            even_ways += 1
        # Pattern 1: 1, 0, 1, 0, ...
        if all(ch == '?' or ch == str((i + 1) % 2) for i, ch in enumerate(even_chars)):
            even_ways += 1
            
        results.append(str((odd_ways * even_ways) % MOD))
        
    print("\n".join(results))

if __name__ == '__main__':
    solve()
