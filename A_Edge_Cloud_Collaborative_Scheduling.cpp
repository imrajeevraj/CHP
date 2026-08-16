#include <bits/stdc++.h>
using namespace std;

double estimate_proc_time(int batch_size, int task_id,
                          const vector<vector<double> >& task_table) {
    if (task_id >= (int)task_table.size())
        return 0.1;

    const vector<double>& row = task_table[task_id];

    if (batch_size >= (int)row.size())
        return row.back();

    return row[(int)batch_size];
}

struct RequestState {
    string stage;
    int computer;
    int Lin;
    int task_id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // ------------------------------------------------------------
    // First line
    // K S SLO1 SLO2 tp_ub tp_base
    // ------------------------------------------------------------

    int K;
    double S, SLO1, SLO2, tp_ub, tp_base;

    cin >> K >> S >> SLO1 >> SLO2 >> tp_ub >> tp_base;

    // ------------------------------------------------------------
    // Second line
    // dist_base tp_th
    // ------------------------------------------------------------

    double dist_base, tp_th;

    cin >> dist_base >> tp_th;

    // ------------------------------------------------------------
    // Number of tasks
    // ------------------------------------------------------------

    int N;
    cin >> N;

    vector<vector<double> > task_table;

    for (int i = 0; i < N; i++) {
        vector<double> row;
        double value;

        string line;
        getline(cin >> ws, line);

        stringstream ss(line);

        while (ss >> value) {
            row.push_back(value);
        }

        task_table.push_back(row);
    }

    // ------------------------------------------------------------
    // Request state
    // ------------------------------------------------------------

    map<int, RequestState> request_state;

    map<int, double> request_arrival_time;

    map<int, double> request_assigned_time;

    // ------------------------------------------------------------
    // Computer state
    // ------------------------------------------------------------

    vector<bool> computer_free(K, true);

    vector<int> computer_request_count(K, 0);

    bool local_free = true;

    // ------------------------------------------------------------
    // Input/output readiness
    // ------------------------------------------------------------

    set<int> input_up_ready;

    set<int> input_down_ready;

    map<int, int> output_iter;

    map<pair<int, int>, bool> output_up_ready;

    map<pair<int, int>, bool> output_down_ready;

    // Same as:
    // num_layers = int(params1[5])
    //
    // params1[5] == tp_base
    // ------------------------------------------------------------

    int num_layers = (int)tp_base;

    // ============================================================
    // MAIN EVENT LOOP
    // ============================================================

    while (true) {

        string timestamp_line;

        cin >> timestamp_line;

        if (timestamp_line == "END")
            break;

        double timestamp = atof(timestamp_line.c_str());

        int num_events;
        cin >> num_events;

        set<int> assigned_this_frame;

        vector<string> assignments;

        // ========================================================
        // PROCESS EVENTS
        // ========================================================

        for (int event_index = 0;
             event_index < num_events;
             event_index++) {

            string event_type;

            cin >> event_type;

            // ====================================================
            // ARR
            // ====================================================

            if (event_type == "ARR") {

                int rid;
                int Lin;

                cin >> rid >> Lin;

                RequestState state;

                state.stage = "P_PRE";
                state.computer = -1;
                state.Lin = Lin;
                state.task_id = rid % N;

                request_state[rid] = state;

                request_arrival_time[rid] = timestamp;

                output_iter[rid] = 0;
            }

            // ====================================================
            // TDN
            // ====================================================

            else if (event_type == "TDN") {

                string server;

                cin >> server;

                if (server == "E") {

                    local_free = true;

                } else {

                    try {

                        int comp_id;

                        if (server.size() > 0 &&
                            server[0] == 'C') {

                            comp_id =
                                atoi(server.substr(1).c_str());

                        } else {

                            comp_id =
                                atoi(server.c_str());
                        }

                        if (comp_id >= 0 &&
                            comp_id < K) {

                            computer_free[comp_id] = true;
                        }

                    } catch (...) {
                        // Same behavior as Python's except ValueError
                    }
                }
            }

            // ====================================================
            // XDN
            // ====================================================

            else if (event_type == "XDN") {

                /*
                    Python:

                    event = input().split()

                    Therefore we must read the complete remaining
                    line and split it exactly like Python.
                */

                string direction;

                cin >> direction;

                string remaining_line;

                getline(cin, remaining_line);

                stringstream ss(remaining_line);

                vector<string> event;

                event.push_back("XDN");
                event.push_back(direction);

                string token;

                while (ss >> token) {
                    event.push_back(token);
                }

                // ------------------------------------------------
                // Same as Python:
                //
                // if len(event) > 6:
                // ------------------------------------------------

                if (event.size() > 6) {

                    string phase = event[4];

                    vector<int> rids;

                    for (int i = 6;
                         i < (int)event.size();
                         i++) {

                        rids.push_back(
                            atoi(event[i].c_str())
                        );
                    }

                    // ------------------------------------------------
                    // UP
                    // ------------------------------------------------

                    if (direction == "UP") {

                        // PRE
                        if (phase == "PRE") {

                            for (int i = 0;
                                 i < (int)rids.size();
                                 i++) {

                                input_up_ready.insert(
                                    rids[i]
                                );
                            }

                        }

                        // DEC
                        else if (phase == "DEC") {

                            for (int i = 0;
                                 i < (int)rids.size();
                                 i++) {

                                int rid = rids[i];

                                pair<int, int> key(
                                    rid,
                                    output_iter[rid]
                                );

                                output_up_ready[key] = true;
                            }
                        }
                    }

                    // ------------------------------------------------
                    // DOWN
                    // ------------------------------------------------

                    else if (direction == "DOWN") {

                        // PRE
                        if (phase == "PRE") {

                            for (int i = 0;
                                 i < (int)rids.size();
                                 i++) {

                                input_down_ready.insert(
                                    rids[i]
                                );
                            }

                        }

                        // DEC
                        else if (phase == "DEC") {

                            for (int i = 0;
                                 i < (int)rids.size();
                                 i++) {

                                int rid = rids[i];

                                pair<int, int> key(
                                    rid,
                                    output_iter[rid]
                                );

                                output_down_ready[key] = true;
                            }
                        }
                    }
                }
            }

            // ====================================================
            // FIN
            // ====================================================

            else if (event_type == "FIN") {

                int rid;

                cin >> rid;

                if (request_state.count(rid)) {

                    int c =
                        request_state[rid].computer;

                    if (c >= 0) {

                        computer_request_count[c] =
                            max(
                                0,
                                computer_request_count[c] - 1
                            );
                    }

                    request_state.erase(rid);
                }

                output_iter.erase(rid);

                request_arrival_time.erase(rid);

                request_assigned_time.erase(rid);
            }
        }

        // ========================================================
        // P_PRE
        // ========================================================

        vector<int> request_ids;

        map<int, RequestState>::iterator request_it;

        for (request_it = request_state.begin();
             request_it != request_state.end();
             ++request_it) {

            request_ids.push_back(
                request_it->first
            );
        }

        sort(
            request_ids.begin(),
            request_ids.end()
        );

        for (int i = 0;
             i < (int)request_ids.size();
             i++) {

            int rid = request_ids[i];

            if (!request_state.count(rid) ||
                assigned_this_frame.count(rid)) {

                continue;
            }

            RequestState& state =
                request_state[rid];

            if (state.stage == "P_PRE" &&
                local_free) {

                int c = -1;

                if (K > 0) {

                    int min_load =
                        *min_element(
                            computer_request_count.begin(),
                            computer_request_count.end()
                        );

                    // --------------------------------------------
                    // First find free computer with minimum load
                    // --------------------------------------------

                    for (int comp = 0;
                         comp < K;
                         comp++) {

                        if (computer_free[comp] &&
                            computer_request_count[comp] ==
                                min_load) {

                            c = comp;

                            break;
                        }
                    }

                    // --------------------------------------------
                    // If none found, choose minimum-load computer
                    // --------------------------------------------

                    if (c == -1) {

                        for (int comp = 0;
                             comp < K;
                             comp++) {

                            if (computer_request_count[comp] ==
                                min_load) {

                                c = comp;

                                break;
                            }
                        }
                    }
                }

                // Same condition as Python:
                //
                // if c is not None or K > 0:
                // --------------------------------------------

                if (c != -1 || K > 0) {

                    if (c == -1)
                        c = 0;

                    assignments.push_back(
                        "E P PRE " +
                        to_string(c) +
                        " " +
                        to_string(rid)
                    );

                    state.computer = c;

                    state.stage = "P_PROC";

                    computer_request_count[c]++;

                    local_free = false;

                    assigned_this_frame.insert(rid);

                    request_assigned_time[rid] =
                        timestamp;
                }
            }
        }

        // ========================================================
        // P_PROC
        // ========================================================

        for (int i = 0;
             i < (int)request_ids.size();
             i++) {

            int rid = request_ids[i];

            if (!request_state.count(rid) ||
                assigned_this_frame.count(rid)) {

                continue;
            }

            RequestState& state =
                request_state[rid];

            if (state.stage == "P_PROC" &&
                input_up_ready.count(rid)) {

                int c = state.computer;

                if (computer_free[c]) {

                    assignments.push_back(
                        "C" +
                        to_string(c) +
                        " P PROC 0 " +
                        to_string(num_layers) +
                        " " +
                        to_string(c) +
                        " " +
                        to_string(rid)
                    );

                    computer_free[c] = false;

                    assigned_this_frame.insert(rid);

                    state.stage = "P_POST";
                }
            }
        }

        // ========================================================
        // P_POST
        // ========================================================

        for (int i = 0;
             i < (int)request_ids.size();
             i++) {

            int rid = request_ids[i];

            if (!request_state.count(rid) ||
                assigned_this_frame.count(rid)) {

                continue;
            }

            RequestState& state =
                request_state[rid];

            if (state.stage == "P_POST" &&
                input_down_ready.count(rid) &&
                local_free) {

                assignments.push_back(
                    "E P POST " +
                    to_string(state.computer) +
                    " " +
                    to_string(rid)
                );

                state.stage = "D_PRE";

                local_free = false;

                assigned_this_frame.insert(rid);
            }
        }

        // ========================================================
        // D_PRE READY
        // ========================================================

        vector<int> d_pre_ready;

        for (int i = 0;
             i < (int)request_state.size();
             i++) {

            int rid = request_ids[i];

            if (!request_state.count(rid))
                continue;

            if (assigned_this_frame.count(rid))
                continue;

            if (request_state[rid].stage == "D_PRE") {

                d_pre_ready.push_back(rid);
            }
        }

        // ========================================================
        // D_PRE GROUPING
        // ========================================================

        if (!d_pre_ready.empty() &&
            local_free) {

            map<int, vector<int> > grouped_by_computer;

            for (int i = 0;
                 i < (int)d_pre_ready.size();
                 i++) {

                int rid = d_pre_ready[i];

                int c =
                    request_state[rid].computer;

                grouped_by_computer[c].push_back(rid);
            }

            vector<int> best_group;

            double best_score = -1;

            // ----------------------------------------------------
            // Same as:
            //
            // for c in sorted(grouped_by_computer.keys()):
            // ----------------------------------------------------

            map<int, vector<int> >::iterator group_it;

            for (group_it = grouped_by_computer.begin();
                 group_it != grouped_by_computer.end();
                 ++group_it) {

                vector<int>& candidates =
                    group_it->second;

                // ------------------------------------------------
                // Python:
                //
                // for group_size in range(
                //     1,
                //     min(5, len(candidates) + 1)
                // ):
                //
                // C++ upper bound is inclusive.
                // ------------------------------------------------

                int max_group_size =
                    min(5, (int)candidates.size());

                for (int group_size = 1;
                     group_size <= max_group_size;
                     group_size++) {

                    vector<int> group(
                        candidates.begin(),
                        candidates.begin() + group_size
                    );

                    double spatial_bonus =
                        group_size * 10.0;

                    vector<double> arrivals;

                    for (int j = 0;
                         j < (int)group.size();
                         j++) {

                        int rid = group[j];

                        arrivals.push_back(
                            request_arrival_time[rid]
                        );
                    }

                    double time_variance = 0;

                    if (!arrivals.empty()) {

                        double min_arrival =
                            *min_element(
                                arrivals.begin(),
                                arrivals.end()
                            );

                        double max_arrival =
                            *max_element(
                                arrivals.begin(),
                                arrivals.end()
                            );

                        time_variance =
                            max_arrival -
                            min_arrival;
                    }

                    double temporal_score;

                    if (time_variance < 100) {

                        temporal_score =
                            -time_variance;

                    } else {

                        temporal_score =
                            -time_variance * 10;
                    }

                    double total_score =
                        spatial_bonus +
                        temporal_score;

                    if (total_score > best_score) {

                        best_score =
                            total_score;

                        best_group =
                            group;
                    }
                }
            }

            // ----------------------------------------------------
            // Python:
            //
            // if best_group is None or len(best_group) < 2:
            //     best_group = d_pre_ready[:min(len(d_pre_ready), 4)]
            // ----------------------------------------------------

            if (best_group.empty() ||
                best_group.size() < 2) {

                int count =
                    min(
                        (int)d_pre_ready.size(),
                        4
                    );

                best_group.assign(
                    d_pre_ready.begin(),
                    d_pre_ready.begin() + count
                );
            }

            // ----------------------------------------------------
            // Create assignment
            // ----------------------------------------------------

            string assignment =
                "E D PRE -1 " +
                to_string(best_group.size());

            for (int i = 0;
                 i < (int)best_group.size();
                 i++) {

                assignment +=
                    " " +
                    to_string(best_group[i]);
            }

            assignments.push_back(assignment);

            // ----------------------------------------------------
            // Update states
            // ----------------------------------------------------

            for (int i = 0;
                 i < (int)best_group.size();
                 i++) {

                int rid =
                    best_group[i];

                request_state[rid].stage =
                    "D_PROC_W";

                assigned_this_frame.insert(rid);
            }

            local_free = false;
        }

        // ========================================================
        // D_PROC
        // ========================================================

        for (int c = 0;
             c < K;
             c++) {

            vector<int> d_proc_ready;

            for (int i = 0;
                 i < (int)request_ids.size();
                 i++) {

                int rid =
                    request_ids[i];

                if (!request_state.count(rid) ||
                    assigned_this_frame.count(rid)) {

                    continue;
                }

                RequestState& state =
                    request_state[rid];

                pair<int, int> key(
                    rid,
                    output_iter[rid]
                );

                if (state.stage == "D_PROC_W" &&
                    state.computer == c &&
                    output_up_ready.count(key)) {

                    d_proc_ready.push_back(rid);
                }
            }

            if (!d_proc_ready.empty() &&
                computer_free[c]) {

                int batch_size =
                    min(
                        (int)d_proc_ready.size(),
                        16
                    );

                vector<int> batch(
                    d_proc_ready.begin(),
                    d_proc_ready.begin() + batch_size
                );

                string assignment =
                    "C" +
                    to_string(c) +
                    " D PROC " +
                    to_string(c) +
                    " " +
                    to_string(batch.size());

                for (int i = 0;
                     i < (int)batch.size();
                     i++) {

                    assignment +=
                        " " +
                        to_string(batch[i]);
                }

                assignments.push_back(assignment);

                for (int i = 0;
                     i < (int)batch.size();
                     i++) {

                    int rid =
                        batch[i];

                    request_state[rid].stage =
                        "D_POST_W";

                    assigned_this_frame.insert(rid);
                }

                computer_free[c] = false;
            }
        }

        // ========================================================
        // D_POST
        // ========================================================

        vector<int> d_post_ready;

        for (int i = 0;
             i < (int)request_ids.size();
             i++) {

            int rid =
                request_ids[i];

            if (!request_state.count(rid) ||
                assigned_this_frame.count(rid)) {

                continue;
            }

            RequestState& state =
                request_state[rid];

            pair<int, int> key(
                rid,
                output_iter[rid]
            );

            if (state.stage == "D_POST_W" &&
                output_down_ready.count(key)) {

                d_post_ready.push_back(rid);
            }
        }

        if (!d_post_ready.empty() &&
            local_free) {

            int batch_size =
                min(
                    (int)d_post_ready.size(),
                    16
                );

            vector<int> batch(
                d_post_ready.begin(),
                d_post_ready.begin() + batch_size
            );

            string assignment =
                "E D POST -1 " +
                to_string(batch.size());

            for (int i = 0;
                 i < (int)batch.size();
                 i++) {

                assignment +=
                    " " +
                    to_string(batch[i]);
            }

            assignments.push_back(assignment);

            for (int i = 0;
                 i < (int)batch.size();
                 i++) {

                int rid =
                    batch[i];

                output_iter[rid]++;

                request_state[rid].stage =
                    "D_PRE";

                assigned_this_frame.insert(rid);
            }

            local_free = false;
        }

        // ========================================================
        // OUTPUT
        // ========================================================

        cout << assignments.size() << '\n';

        for (int i = 0;
             i < (int)assignments.size();
             i++) {

            cout << assignments[i] << '\n';
        }

        cout.flush();
    }

    return 0;
}