t = int(input())

for _ in range(t):
    n = int(input())
    my_list = list(map(int, input().split()))
    my_list.sort()
    if (my_list[0] == my_list[- 1]):
        print("NO")
    else:
        print("YES")
        print(my_list[-1], end =" ")
        for i in range(n-1):
            print(my_list[i], end = " ")
        print()



    