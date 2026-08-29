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
        n = int(data[idx])
        m = int(data[idx + 1])
        idx += 2
        
        # Original words
        available_letters = set()
        for _ in range(n):
            w = data[idx]
            available_letters.add(w[0].upper())
            idx += 1
            
        # Abbreviations
        valid = True
        for _ in range(m):
            abbr = data[idx]
            idx += 1
            if valid:
                for ch in abbr:
                    if ch not in available_letters:
                        valid = False
                        break
                        
        if valid:
            results.append("YES")
        else:
            results.append("NO")
            
    print("\n".join(results))

if __name__ == '__main__':
    solve()
