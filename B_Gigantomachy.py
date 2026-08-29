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
        
        a1 = int(data[idx])
        idx += n  # skip remaining heights for Bea
        
        b1 = int(data[idx])
        idx += m  # skip remaining heights for Ver
        
        # Bea (Giant 1) can take a1 + n - 1 hits
        # Ver (Giant 2) can take b1 + m - 1 hits
        # Since Bea goes first, Bea wins if (a1 + n - 1) >= (b1 + m - 1)
        if a1 + n >= b1 + m:
            results.append("1")
        else:
            results.append("2")
            
    print("\n".join(results))

if __name__ == '__main__':
    solve()
