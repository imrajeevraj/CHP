import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    t = int(data[0])
    results = []
    idx = 1
    
    for _ in range(t):
        a = int(data[idx])
        b = int(data[idx + 1])
        c = int(data[idx + 2])
        idx += 3
        
        rounds = 0
        arr = [a, b, c]
        while True:
            if arr[0] == arr[1] or arr[1] == arr[2] or arr[0] == arr[2]:
                break
            arr.sort()
            arr[0] += 1
            arr[2] -= 1
            rounds += 1
            
        results.append(str(rounds))
        
    print("\n".join(results))

if __name__ == '__main__':
    solve()
