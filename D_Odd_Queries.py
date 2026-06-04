t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    
    odd_count = sum(1 for x in a if x % 2 == 1)
    original_parity = odd_count % 2

    prefix = [0] * (n + 1)
    for i in range(n):
        prefix[i + 1] = prefix[i] + (1 if a[i] % 2 == 1 else 0)
    
    for _ in range(q):
        l, r, k = map(int, input().split())

        odd_in_range = prefix[r] - prefix[l - 1]
        sum_parity = odd_in_range % 2
        
       
        range_length = r - l + 1
        product_parity = (range_length % 2) * (k % 2)
        
        new_parity = (original_parity + sum_parity + product_parity) % 2
        
        print("YES" if new_parity == 1 else "NO")
