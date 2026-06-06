t = int(input())

for _ in range(t):
    a, b, c = map(int, input().split())
    ok = False


    if (2*b - c) > 0 and (2*b - c) % a == 0:
        ok = True

   
    if not ok and (a + c) % (2*b) == 0:
        ok = True

   
    if not ok and (2*b - a) > 0 and (2*b - a) % c == 0:
        ok = True

    print("YES" if ok else "NO")