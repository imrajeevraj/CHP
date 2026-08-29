import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    t = int(data[0])
    idx = 1
    out = []
    
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        
        parents = [int(x) for x in data[idx : idx + n - 1]]
        idx += n - 1
        
        m = int(data[idx])
        idx += 1
        
        dams = [int(x) for x in data[idx : idx + m]]
        idx += m
        
        adj = [[] for _ in range(n + 1)]
        for i, p in enumerate(parents):
            u = i + 2
            adj[p].append(u)
            
        is_dam = [False] * (n + 1)
        for d in dams:
            is_dam[d] = True
            
        cnt = [0] * (n + 1)
        for u in range(n, 0, -1):
            if is_dam[u]:
                cnt[u] += 1
            if u > 1:
                cnt[parents[u - 2]] += cnt[u]
                
        INF = 10**9
        dp0 = [INF] * (n + 1)
        dp1 = [INF] * (n + 1)
        best_c0 = [INF] * (n + 1)
        best_c0_choice = [0] * (n + 1)
        
        for u in range(n, 0, -1):
            if cnt[u] == 0:
                continue
                
            children = [v for v in adj[u] if cnt[v] > 0]
            
            for v in children:
                c_no_cam = dp0[v]
                c_with_cam = dp1[v] + 1
                if c_no_cam <= c_with_cam:
                    best_c0[v] = c_no_cam
                    best_c0_choice[v] = 0
                else:
                    best_c0[v] = c_with_cam
                    best_c0_choice[v] = 1
                    
            S = sum(best_c0[v] for v in children)
            
            if is_dam[u]:
                dp0[u] = INF
                dp1[u] = S
            else:
                dp0[u] = S
                min_diff = INF
                for v in children:
                    diff = dp1[v] - best_c0[v]
                    if diff < min_diff:
                        min_diff = diff
                dp1[u] = S + min_diff if children else INF
                
        cameras = []
        root_state = 0 if dp0[1] <= dp1[1] else 1
        stack = [(1, root_state)]
        
        while stack:
            u, state = stack.pop()
            children = [v for v in adj[u] if cnt[v] > 0]
            
            if is_dam[u]:
                for v in children:
                    if best_c0_choice[v] == 1:
                        cameras.append(v)
                        stack.append((v, 1))
                    else:
                        stack.append((v, 0))
            else:
                if state == 0:
                    for v in children:
                        if best_c0_choice[v] == 1:
                            cameras.append(v)
                            stack.append((v, 1))
                        else:
                            stack.append((v, 0))
                else:
                    best_v = None
                    min_diff = INF
                    for v in children:
                        diff = dp1[v] - best_c0[v]
                        if diff < min_diff:
                            min_diff = diff
                            best_v = v
                    for v in children:
                        if v == best_v:
                            stack.append((v, 1))
                        else:
                            if best_c0_choice[v] == 1:
                                cameras.append(v)
                                stack.append((v, 1))
                            else:
                                stack.append((v, 0))
                                
        if cameras:
            out.append(f"{len(cameras)} " + " ".join(map(str, cameras)))
        else:
            out.append("0")
            
    print("\n".join(out))

if __name__ == '__main__':
    solve()
