import sys
input = sys.stdin.readline

def solve():
    n = int(input())
    s = input().strip()
    
    first_occ = [-1] * 26
    for i in range(n):
        c = ord(s[i]) - ord('a')
        if first_occ[c] == -1:
            first_occ[c] = i
    
    ans = 0
    for c in range(26):
        if first_occ[c] != -1:
            ans += (n - first_occ[c])
    
    print(ans)

t = int(input())
for _ in range(t):
    solve()