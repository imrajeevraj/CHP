t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))

    cur = a[0]      # Maximum valid subarray sum ending at current index
    ans = a[0]      # Overall maximum sum

    for i in range(1, n):
        # Check if current and previous elements have different parity
        if abs(a[i] % 2) != abs(a[i - 1] % 2):
            # Either extend the previous subarray or start a new one
            cur = max(a[i], cur + a[i])
        else:
            # Same parity, so start a new subarray
            cur = a[i]

        ans = max(ans, cur)

    print(ans)