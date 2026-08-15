
import sys

def estimate_proc_time(batch_size, task_id, task_table):
    """Estimate processing time for a batch of requests on a task"""
    if task_id >= len(task_table):
        return 0.1
    row = task_table[task_id]
    
    if batch_size >= len(row):
        return row[-1]
    return row[int(batch_size)]

def main():
    params1 = input().split()
    K = int(params1[0])
    S = float(params1[1])
    SLO1 = float(params1[2])
    SLO2 = float(params1[3])
    tp_ub = float(params1[4])
    tp_base = float(params1[5])
    
    params2 = input().split()
    dist_base = float(params2[0])
    tp_th = float(params2[1])
    
    N = int(input())
    task_table = []
    for _ in range(N):
        row = list(map(float, input().split()))
        task_table.append(row)
    
    request_state = {}
    request_arrival_time = {}
    request_assigned_time = {}
    computer_free = [True] * K
    computer_request_count = [0] * K
    local_free = True
    input_up_ready = set()
    input_down_ready = set()
    output_iter = {}
    output_up_ready = {}
    output_down_ready = {}
    
    num_layers = int(params1[5])
    
    while True:
        timestamp_line = input().strip()
        if timestamp_line == "END":
            break
        
        timestamp = float(timestamp_line)
        num_events = int(input())
        
        assigned_this_frame = set()
        
        for _ in range(num_events):
            event = input().split()
            
            if event[0] == "ARR":
                rid = int(event[1])
                Lin = int(event[2])
                request_state[rid] = {
                    'stage': 'P_PRE',
                    'computer': None,
                    'Lin': Lin,
                    'task_id': rid % N
                }
                request_arrival_time[rid] = timestamp
                output_iter[rid] = 0
            
            elif event[0] == "TDN":
                server = event[1]
                if server == 'E':
                    local_free = True
                else:
                    try:
                        comp_id = int(server[1:]) if server.startswith('C') else int(server)
                        if 0 <= comp_id < K:
                            computer_free[comp_id] = True
                    except ValueError:
                        pass
            
            elif event[0] == "XDN":
                direction = event[1]
                if len(event) > 6:
                    phase = event[4]
                    rids = [int(event[i]) for i in range(6, len(event))]
                    
                    if direction == "UP":
                        if phase == "PRE":
                            input_up_ready.update(rids)
                        elif phase == "DEC":
                            for rid in rids:
                                key = (rid, output_iter[rid])
                                output_up_ready[key] = True
                    elif direction == "DOWN":
                        if phase == "PRE":
                            input_down_ready.update(rids)
                        elif phase == "DEC":
                            for rid in rids:
                                key = (rid, output_iter[rid])
                                output_down_ready[key] = True
            
            elif event[0] == "FIN":
                rid = int(event[1])
                if rid in request_state:
                    c = request_state[rid]['computer']
                    if c is not None and c >= 0:
                        computer_request_count[c] = max(0, computer_request_count[c] - 1)
                    del request_state[rid]
                output_iter.pop(rid, None)
                request_arrival_time.pop(rid, None)
                request_assigned_time.pop(rid, None)
        
        assignments = []
        
        
        for rid in sorted(list(request_state.keys())):
            if rid not in request_state or rid in assigned_this_frame:
                continue
            
            state = request_state[rid]
            if state['stage'] == 'P_PRE' and local_free:
                c = None
                if K > 0:
                    min_load = min(computer_request_count)
                    for comp in range(K):
                        if computer_free[comp] and computer_request_count[comp] == min_load:
                            c = comp
                            break
                    if c is None:
                        for comp in range(K):
                            if computer_request_count[comp] == min_load:
                                c = comp
                                break
                if c is not None or K > 0:
                    c = c if c is not None else 0
                    assignments.append(f"E P PRE {c} {rid}")
                    state['computer'] = c
                    state['stage'] = 'P_PROC'
                    computer_request_count[c] += 1
                    local_free = False
                    assigned_this_frame.add(rid)
                    request_assigned_time[rid] = timestamp
        
        
        for rid in sorted(list(request_state.keys())):
            if rid not in request_state or rid in assigned_this_frame:
                continue
            
            state = request_state[rid]
            if state['stage'] == 'P_PROC' and rid in input_up_ready:
                c = state['computer']
                if computer_free[c]:
                    assignments.append(f"C{c} P PROC 0 {num_layers} {c} {rid}")
                    computer_free[c] = False
                    assigned_this_frame.add(rid)
                    state['stage'] = 'P_POST'
        
       
        for rid in sorted(list(request_state.keys())):
            if rid not in request_state or rid in assigned_this_frame:
                continue
            
            state = request_state[rid]
            if state['stage'] == 'P_POST' and rid in input_down_ready and local_free:
                assignments.append(f"E P POST {state['computer']} {rid}")
                state['stage'] = 'D_PRE'
                local_free = False
                assigned_this_frame.add(rid)
        
        d_pre_ready = [rid for rid in sorted(request_state.keys()) 
                       if rid not in assigned_this_frame and request_state[rid]['stage'] == 'D_PRE']
        
        if d_pre_ready and local_free:
            
            grouped_by_computer = {}
            for rid in d_pre_ready:
                c = request_state[rid]['computer']
                if c not in grouped_by_computer:
                    grouped_by_computer[c] = []
                grouped_by_computer[c].append(rid)
            
            
            best_group = None
            best_score = -1
            
            
            for c in sorted(grouped_by_computer.keys()):
                candidates = grouped_by_computer[c]
                for group_size in range(1, min(5, len(candidates) + 1)):
                    group = candidates[:group_size]
                    
                
                    spatial_bonus = group_size * 10
                    arrivals = [request_arrival_time[rid] for rid in group]
                    time_variance = max(arrivals) - min(arrivals) if arrivals else 0
                    temporal_score = -time_variance if time_variance < 100 else -time_variance * 10
                    
                    total_score = spatial_bonus + temporal_score
                    if total_score > best_score:
                        best_score = total_score
                        best_group = group
            
            
            if best_group is None or len(best_group) < 2:
                best_group = d_pre_ready[:min(len(d_pre_ready), 4)]
            
            assignments.append(f"E D PRE -1 {len(best_group)} " + " ".join(map(str, best_group)))
            for rid in best_group:
                request_state[rid]['stage'] = 'D_PROC_W'
                assigned_this_frame.add(rid)
            local_free = False
        
        for c in range(K):
            d_proc_ready = [rid for rid in sorted(request_state.keys())
                            if rid not in assigned_this_frame and request_state[rid]['stage'] == 'D_PROC_W'
                            and request_state[rid]['computer'] == c
                            and (rid, output_iter[rid]) in output_up_ready]
            if d_proc_ready and computer_free[c]:
                
                batch = d_proc_ready[:min(len(d_proc_ready), 16)]
                assignments.append(f"C{c} D PROC {c} {len(batch)} " + " ".join(map(str, batch)))
                for rid in batch:
                    request_state[rid]['stage'] = 'D_POST_W'
                    assigned_this_frame.add(rid)
                computer_free[c] = False
        
        d_post_ready = [rid for rid in sorted(request_state.keys())
                        if rid not in assigned_this_frame and request_state[rid]['stage'] == 'D_POST_W'
                        and (rid, output_iter[rid]) in output_down_ready]
        if d_post_ready and local_free:
            batch = d_post_ready[:min(len(d_post_ready), 16)]
            assignments.append(f"E D POST -1 {len(batch)} " + " ".join(map(str, batch)))
            for rid in batch:
                output_iter[rid] += 1
                request_state[rid]['stage'] = 'D_PRE'
                assigned_this_frame.add(rid)
            local_free = False
        
        print(len(assignments))
        for assignment in assignments:
            print(assignment)
        
        sys.stdout.flush()

if __name__ == "__main__":
    main()

