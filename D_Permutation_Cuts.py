import sys

def solve():
    # Fast I/O for large inputs (sum of n <= 10^6)
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    t = int(next(iterator))
    
    MOD = 998244353
    out = []
    
    for _ in range(t):
        n = int(next(iterator))
        a = [0] * n
        max_a = 0
        
        for i in range(1, n):
            a[i] = int(next(iterator))
            if a[i] > max_a:
                max_a = a[i]
        
        # The peak value in 'a' must be exactly n - 1
        if max_a != n - 1:
            out.append("0")
            continue
        
        # Find first and last occurrences of the peak value n - 1
        L_M = -1
        R_M = -1
        for i in range(1, n):
            if a[i] == n - 1:
                if L_M == -1:
                    L_M = i
                R_M = i
        
        # Validate unimodality of 'a'
        unimodal = True
        for i in range(1, L_M):
            if a[i] > a[i + 1]:
                unimodal = False
                break
        if unimodal:
            for i in range(R_M, n - 1):
                if a[i] < a[i + 1]:
                    unimodal = False
                    break
        if unimodal:
            for i in range(L_M, R_M + 1):
                if a[i] != n - 1:
                    unimodal = False
                    break
        
        if not unimodal:
            out.append("0")
            continue
        
        # Two pointers tracking cuts >= x
        l = L_M
        r = R_M
        
        # Bounding box of positions reserved for elements placed so far
        U = L_M
        V = R_M + 1
        
        ways = 2  # 2 ways to place n and n-1
        C = 2     # Count of elements placed so far
        
        possible = True
        for x in range(n - 2, 0, -1):
            while l > 1 and a[l - 1] >= x:
                l -= 1
            while r < n - 1 and a[r + 1] >= x:
                r += 1
            
            expand_left = (l < U)
            expand_right = (r > V - 1)
            
            if expand_left and expand_right:
                # Cannot satisfy expansion on both sides with a single element
                possible = False
                break
            elif expand_left:
                U = l
                C += 1
            elif expand_right:
                V = r + 1
                C += 1
            else:
                # Box didn't expand, place x in any available empty spot
                avail = (V - U + 1) - C
                if avail <= 0:
                    possible = False
                    break
                ways = (ways * avail) % MOD
                C += 1
        
        if not possible:
            out.append("0")
        else:
            out.append(str(ways))
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()