import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    t = int(input_data[idx])
    idx += 1
    
    out = []
    for _ in range(t):
        n = int(input_data[idx])
        k = int(input_data[idx+1])
        idx += 2
        grid = []
        for _ in range(n):
            grid.append([int(x) for x in input_data[idx:idx+n]])
            idx += n
        diff = 0
        for i in range(n):
            for j in range(n):
                if grid[i][j] != grid[n - 1 - i][n - 1 - j]:
                    diff += 1
        diff //= 2
        
        if k < diff:
            out.append("NO")
        else:
            rem = k - diff
            if n % 2 == 1:
                out.append("YES")
            else:
                if rem % 2 == 0:
                    out.append("YES")
                else:
                    out.append("NO")
                    
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()
