t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    s = input()
    freq = {}
    for c in s:
        freq[c] = freq.get(c, 0) + 1
    
    odd = sum(1 for count in freq.values() if count % 2 == 1)

    if odd <= k + 1:
        print("YES")
    else:
        print("NO")
  
