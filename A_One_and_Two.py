t = int(input())

for _ in range(t):
    n = int(input())
    my_list = list(map(int, input().split()))
    count = my_list.count(2)

    if count % 2:
        print(-1)
        continue
    if count == 0:
        print(1)
        continue
    need = count // 2
    c = 0
    for i in range(n):
        if my_list[i] == 2:
            c+=1

        if c == need:
            print(i +1)
            break
        