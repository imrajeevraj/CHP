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
        c = int(data[idx + 1])
        idx += 2
        
        # 1-indexed costs: a[i] + i
        costs = [int(data[idx + i - 1]) + i for i in range(1, n + 1)]
        idx += n
        
        costs.sort()
        
        count = 0
        for cost in costs:
            if c >= cost:
                c -= cost
                count += 1
            else:
                break
                
        out.append(str(count))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()