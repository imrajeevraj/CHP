import sys
import heapq

def main():
    input = sys.stdin.buffer.readline

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
        task_table.append(list(map(float, input().split())))

    request_state = {}
    request_arrival_time = {}
    output_iter = {}

    computer_free = [True] * K
    computer_request_count = [0] * K
    local_free = True

    input_up_ready = set()
    input_down_ready = set()
    output_up_ready = set()
    output_down_ready = set()

    p_pre_heap = []
    p_proc_heaps = [[] for _ in range(K)]
    d_pre_heaps = [[] for _ in range(K)]
    d_proc_heaps = [[] for _ in range(K)]
    d_pre_global = []
    d_post_heap = []

    def valid(rid, stage):
        state = request_state.get(rid)
        return state is not None and state[0] == stage

    def clean_heap(heap, stage):
        while heap:
            rid = heap[0]
            if valid(rid, stage):
                break
            heapq.heappop(heap)

    def peek_valid(heap, stage, limit):
        result = []

        while heap and len(result) < limit:
            rid = heapq.heappop(heap)

            if valid(rid, stage):
                result.append(rid)

        for rid in result:
            heapq.heappush(heap, rid)

        return result

    def add_p_proc(rid):
        state = request_state.get(rid)
        if state is not None and state[0] == 'P_PROC':
            heapq.heappush(p_proc_heaps[state[1]], rid)

    def add_d_pre(rid):
        state = request_state.get(rid)
        if state is not None and state[0] == 'D_PRE':
            c = state[1]
            heapq.heappush(d_pre_heaps[c], rid)
            heapq.heappush(d_pre_global, rid)

    def add_d_proc(rid):
        state = request_state.get(rid)
        if state is not None and state[0] == 'D_PROC_W':
            c = state[1]
            if (rid, output_iter[rid]) in output_up_ready:
                heapq.heappush(d_proc_heaps[c], rid)

    def add_d_post(rid):
        state = request_state.get(rid)
        if state is not None and state[0] == 'D_POST_W':
            if (rid, output_iter[rid]) in output_down_ready:
                heapq.heappush(d_post_heap, rid)

    while True:
        timestamp_line = input().strip()

        if timestamp_line == b"END":
            break

        timestamp = float(timestamp_line)
        num_events = int(input())

        assigned_this_frame = set()

        for _ in range(num_events):
            event = input().split()
            event_type = event[0]

            if event_type == b"ARR":
                rid = int(event[1])
                Lin = int(event[2])

                request_state[rid] = ['P_PRE', -1, Lin]
                request_arrival_time[rid] = timestamp
                output_iter[rid] = 0

                heapq.heappush(p_pre_heap, rid)

            elif event_type == b"TDN":
                server = event[1]

                if server == b'E':
                    local_free = True
                else:
                    try:
                        if server.startswith(b'C'):
                            comp_id = int(server[1:])
                        else:
                            comp_id = int(server)

                        if 0 <= comp_id < K:
                            computer_free[comp_id] = True
                    except ValueError:
                        pass

            elif event_type == b"XDN":
                direction = event[1]

                if len(event) <= 6:
                    continue

                phase = event[4]
                rids = [int(event[i]) for i in range(6, len(event))]

                if direction == b"UP":
                    if phase == b"PRE":
                        for rid in rids:
                            input_up_ready.add(rid)
                            state = request_state.get(rid)

                            if state is not None and state[0] == 'P_PROC':
                                add_p_proc(rid)

                    elif phase == b"DEC":
                        for rid in rids:
                            key = (rid, output_iter[rid])
                            output_up_ready.add(key)
                            state = request_state.get(rid)

                            if state is not None and state[0] == 'D_PROC_W':
                                add_d_proc(rid)

                elif direction == b"DOWN":
                    if phase == b"PRE":
                        for rid in rids:
                            input_down_ready.add(rid)

                    elif phase == b"DEC":
                        for rid in rids:
                            key = (rid, output_iter[rid])
                            output_down_ready.add(key)
                            state = request_state.get(rid)

                            if state is not None and state[0] == 'D_POST_W':
                                add_d_post(rid)

            elif event_type == b"FIN":
                rid = int(event[1])
                state = request_state.get(rid)

                if state is not None:
                    c = state[1]
                    if c >= 0:
                        computer_request_count[c] -= 1
                    del request_state[rid]

                output_iter.pop(rid, None)
                request_arrival_time.pop(rid, None)

        assignments = []

        if local_free and p_pre_heap and K > 0:
            clean_heap(p_pre_heap, 'P_PRE')

            if p_pre_heap:
                rid = heapq.heappop(p_pre_heap)
                state = request_state.get(rid)

                if state is not None and state[0] == 'P_PRE':
                    min_load = min(computer_request_count)
                    c = -1

                    for comp in range(K):
                        if computer_free[comp] and computer_request_count[comp] == min_load:
                            c = comp
                            break

                    if c == -1:
                        for comp in range(K):
                            if computer_request_count[comp] == min_load:
                                c = comp
                                break

                    if c == -1:
                        c = 0

                    assignments.append(f"E P PRE {c} {rid}")

                    state[0] = 'P_PROC'
                    state[1] = c

                    computer_request_count[c] += 1
                    local_free = False
                    assigned_this_frame.add(rid)

                    if rid in input_up_ready:
                        heapq.heappush(p_proc_heaps[c], rid)

        for c in range(K):
            if not computer_free[c]:
                continue

            heap = p_proc_heaps[c]
            clean_heap(heap, 'P_PROC')

            if not heap:
                continue

            rid = heapq.heappop(heap)
            state = request_state.get(rid)

            if state is None or state[0] != 'P_PROC':
                continue

            assignments.append(
                f"C{c} P PROC 0 {int(tp_base)} {c} {rid}"
            )

            computer_free[c] = False
            state[0] = 'P_POST'
            assigned_this_frame.add(rid)

        if local_free:
            best_rid = None

            for rid, state in request_state.items():
                if (
                    rid not in assigned_this_frame
                    and state[0] == 'P_POST'
                    and rid in input_down_ready
                ):
                    if best_rid is None or rid < best_rid:
                        best_rid = rid

            if best_rid is not None:
                rid = best_rid
                state = request_state[rid]

                assignments.append(
                    f"E P POST {state[1]} {rid}"
                )

                state[0] = 'D_PRE'
                local_free = False
                assigned_this_frame.add(rid)

                add_d_pre(rid)

        if local_free:
            best_group = None
            best_score = -1

            for c in range(K):
                candidates = peek_valid(
                    d_pre_heaps[c],
                    'D_PRE',
                    5
                )

                if not candidates:
                    continue

                max_group = min(5, len(candidates))

                for group_size in range(1, max_group + 1):
                    group = candidates[:group_size]

                    arrivals = [
                        request_arrival_time[rid]
                        for rid in group
                    ]

                    time_variance = (
                        max(arrivals) - min(arrivals)
                        if arrivals
                        else 0
                    )

                    spatial_bonus = group_size * 10

                    if time_variance < 100:
                        temporal_score = -time_variance
                    else:
                        temporal_score = -time_variance * 10

                    total_score = spatial_bonus + temporal_score

                    if total_score > best_score:
                        best_score = total_score
                        best_group = group

            if best_group is None or len(best_group) < 2:
                best_group = peek_valid(
                    d_pre_global,
                    'D_PRE',
                    4
                )

            if best_group:
                assignments.append(
                    f"E D PRE -1 {len(best_group)} "
                    + " ".join(map(str, best_group))
                )

                for rid in best_group:
                    state = request_state.get(rid)

                    if state is not None and state[0] == 'D_PRE':
                        state[0] = 'D_PROC_W'
                        assigned_this_frame.add(rid)
                        add_d_proc(rid)

                local_free = False

        for c in range(K):
            if not computer_free[c]:
                continue

            heap = d_proc_heaps[c]
            clean_heap(heap, 'D_PROC_W')

            if not heap:
                continue

            batch = []

            while heap and len(batch) < 16:
                rid = heapq.heappop(heap)
                state = request_state.get(rid)

                if (
                    state is not None
                    and state[0] == 'D_PROC_W'
                    and (rid, output_iter[rid]) in output_up_ready
                ):
                    batch.append(rid)

            if not batch:
                continue

            assignments.append(
                f"C{c} D PROC {c} {len(batch)} "
                + " ".join(map(str, batch))
            )

            for rid in batch:
                state = request_state.get(rid)

                if state is not None:
                    state[0] = 'D_POST_W'
                    assigned_this_frame.add(rid)
                    add_d_post(rid)

            computer_free[c] = False

        if local_free:
            clean_heap(d_post_heap, 'D_POST_W')

            if d_post_heap:
                batch = []

                while d_post_heap and len(batch) < 16:
                    rid = heapq.heappop(d_post_heap)
                    state = request_state.get(rid)

                    if (
                        state is not None
                        and state[0] == 'D_POST_W'
                        and (rid, output_iter[rid]) in output_down_ready
                    ):
                        batch.append(rid)

                if batch:
                    assignments.append(
                        f"E D POST -1 {len(batch)} "
                        + " ".join(map(str, batch))
                    )

                    for rid in batch:
                        state = request_state.get(rid)

                        if state is not None:
                            output_iter[rid] += 1
                            state[0] = 'D_PRE'
                            assigned_this_frame.add(rid)
                            add_d_pre(rid)

                    local_free = False

        sys.stdout.write(str(len(assignments)) + '\n')

        if assignments:
            sys.stdout.write('\n'.join(assignments) + '\n')

        sys.stdout.flush()


if __name__ == "__main__":
    main()