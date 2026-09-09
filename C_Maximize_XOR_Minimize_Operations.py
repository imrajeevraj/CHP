import sys

def main():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    t = int(data[0])
    out = []
    idx = 1
    
    for _ in range(t):
        x = int(data[idx])
        y = int(data[idx + 1])
        idx += 2
        
        S = x + y
        diff = y & (~S)
        
        if diff == 0:
            out.append(f"{S} 0")
            continue
        
        p = diff.bit_length() - 1
        
        best_bit = -1
        for i in range(p + 1, 62):
            if ((S >> i) & 1) and not ((y >> i) & 1):
                best_bit = i
                break
        
        b = ((y >> (best_bit + 1)) << (best_bit + 1)) | (1 << best_bit)
        out.append(f"{S} {b - y}")
        
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()