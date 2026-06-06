t = int(input())

for _ in range(t):
    s = input()

    zero = s.count('0')
    one = s.count('1')

    ans = 0

    for i in range(len(s)):
        if s[i] == '0':
            if one > 0:
                one -= 1
            else:
                ans = len(s) - i
                break
        else:
            if zero > 0:
                zero -= 1
            else:
                ans = len(s) - i
                break

    print(ans)