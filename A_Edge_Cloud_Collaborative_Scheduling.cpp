#include <bits/stdc++.h>
using namespace std;

double estimate_proc_time(int batch_size, int task_id,
                          const vector<vector<double>>& task_table) {
    if (task_id >= (int)task_table.size())
        return 0.1;

    const auto& row = task_table[task_id];

    if (batch_size >= (int)row.size())
        return row.back();

    return row[(int)batch_size];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    double S, SLO1, SLO2, tp_ub, tp_base;

    cin >> K >> S >> SLO1 >> SLO2 >> tp_ub >> tp_base;

    double dist_base, tp_th;
    cin >> dist_base >> tp_th;

    int N;
    cin >> N;

    vector<vector<double>> task_table(N);

    for (int i = 0; i < N; i++) {
        string line;
        getline(cin >> ws, line);

        stringstream ss(line);
        double x;

        while (ss >> x)
            task_table[i].push_back(x);
    }

    struct RequestState {
        string stage;
        int computer;
        int Lin;
        int task_id;
    };

    unordered_map<int, RequestState> request_state;
    unordered_map<int, double> request_arrival_time;
    unordered_map<int, double> request_assigned_time;

    vector<bool> computer_free(K, true);
    vector<int> computer_request_count(K, 0);

    bool local_free = true;

    unordered_set<int> input_up_ready;
    unordered_set<int> input_down_ready;

    unordered_map<int, int> output_iter;

    set<pair<int, int>> output_up_ready;
    set<pair<int, int>> output_down_ready;

    int num_layers = (int)tp_base;

    while (true) {
        string timestamp_line;
        cin >> timestamp_line;

        if (timestamp_line == "END")
            break;

        double timestamp = stod(timestamp_line);

        int num_events;
        cin >> num_events;

        unordered_set<int> assigned_this_frame;
        vector<string> assignments;

        for (int i = 0; i < num_events; i++) {
            vector<string> event;
            string token;

            cin >> token;
            event.push_back(token);

            if (token == "ARR") {
                string s1, s2;
                cin >> s1 >> s2;

                event.push_back(s1);
                event.push_back(s2);

                int rid = stoi(s1);
                int Lin = stoi(s2);

                request_state[rid] = {
                    "P_PRE",
                    -1,
                    Lin,
                    rid % N
                };

                request_arrival_time[rid] = timestamp;
                output_iter[rid] = 0;
            }

            else if (token == "TDN") {
                string server;
                cin >> server;

                if (server == "E") {
                    local_free = true;
                } else {
                    try {
                        int comp_id;

                        if (server.size() > 1 && server[0] == 'C')
                            comp_id = stoi(server.substr(1));
                        else
                            comp_id = stoi(server);

                        if (0 <= comp_id && comp_id < K)
                            computer_free[comp_id] = true;

                    } catch (...) {
                    }
                }
            }

            else if (token == "XDN") {
                string direction;
                cin >> direction;

                event.push_back(direction);

                /*
                    Original Python code only processes the event
                    if len(event) > 6.

                    We therefore read the remaining tokens of the
                    current line.
                */
                string line;
                getline(cin, line);

                stringstream ss(line);
                string x;

                while (ss >> x)
                    event.push_back(x);

                if (event.size() > 6) {
                    string phase = event[4];

                    vector<int> rids;

                    for (int j = 6; j < (int)event.size(); j++)
                        rids.push_back(stoi(event[j]));

                    if (direction == "UP") {
                        if (phase == "PRE") {
                            for (int rid : rids)
                                input_up_ready.insert(rid);
                        }
                        else if (phase == "DEC") {
                            for (int rid : rids) {
                                pair<int, int> key = {
                                    rid,
                                    output_iter[rid]
                                };

                                output_up_ready.insert(key);
                            }
                        }
                    }

                    else if (direction == "DOWN") {
                        if (phase == "PRE") {
                            for (int rid : rids)
                                input_down_ready.insert(rid);
                        }
                        else if (phase == "DEC") {
                            for (int rid : rids) {
                                pair<int, int> key = {
                                    rid,
                                    output_iter[rid]
                                };

                                output_down_ready.insert(key);
                            }
                        }
                    }
                }
            }

            else if (token == "FIN") {
                string s;
                cin >> s;

                int rid = stoi(s);

                if (request_state.count(rid)) {
                    int c = request_state[rid].computer;

                    if (c >= 0 && c < K) {
                        computer_request_count[c] =
                            max(0, computer_request_count[c] - 1);
                    }

                    request_state.erase(rid);
                }

                output_iter.erase(rid);
                request_arrival_time.erase(rid);
                request_assigned_time.erase(rid);
            }
        }

        // --------------------------------------------------
        // P_PRE
        // --------------------------------------------------

        vector<int> request_ids;

        for (auto& [rid, state] : request_state)
            request_ids.push_back(rid);

        sort(request_ids.begin(), request_ids.end());

        for (int rid : request_ids) {
            if (!request_state.count(rid))
                continue;

            if (assigned_this_frame.count(rid))
                continue;

            auto& state = request_state[rid];

            if (state.stage == "P_PRE" && local_free) {
                int c = -1;

                if (K > 0) {
                    int min_load =
                        *min_element(
                            computer_request_count.begin(),
                            computer_request_count.end()
                        );

                    for (int comp = 0; comp < K; comp++) {
                        if (computer_free[comp] &&
                            computer_request_count[comp] == min_load) {

                            c = comp;
                            break;
                        }
                    }

                    if (c == -1) {
                        for (int comp = 0; comp < K; comp++) {
                            if (computer_request_count[comp] ==
                                min_load) {

                                c = comp;
                                break;
                            }
                        }
                    }
                }

                if (c != -1 || K > 0) {
                    if (c == -1)
                        c = 0;

                    assignments.push_back(
                        "E P PRE " +
                        to_string(c) + " " +
                        to_string(rid)
                    );

                    state.computer = c;
                    state.stage = "P_PROC";

                    computer_request_count[c]++;

                    local_free = false;
                    assigned_this_frame.insert(rid);

                    request_assigned_time[rid] = timestamp;
                }
            }
        }

        // --------------------------------------------------
        // P_PROC
        // --------------------------------------------------

        for (int rid : request_ids) {
            if (!request_state.count(rid))
                continue;

            if (assigned_this_frame.count(rid))
                continue;

            auto& state = request_state[rid];

            if (state.stage == "P_PROC" &&
                input_up_ready.count(rid)) {

                int c = state.computer;

                if (computer_free[c]) {
                    assignments.push_back(
                        "C" + to_string(c) +
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

        // --------------------------------------------------
        // P_POST
        // --------------------------------------------------

        for (int rid : request_ids) {
            if (!request_state.count(rid))
                continue;

            if (assigned_this_frame.count(rid))
                continue;

            auto& state = request_state[rid];

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

        // --------------------------------------------------
        // D_PRE
        // --------------------------------------------------

        vector<int> d_pre_ready;

        for (int rid : request_ids) {
            if (!request_state.count(rid))
                continue;

            if (assigned_this_frame.count(rid))
                continue;

            if (request_state[rid].stage == "D_PRE")
                d_pre_ready.push_back(rid);
        }

        if (!d_pre_ready.empty() && local_free) {
            map<int, vector<int>> grouped_by_computer;

            for (int rid : d_pre_ready) {
                int c = request_state[rid].computer;
                grouped_by_computer[c].push_back(rid);
            }

            vector<int> best_group;
            double best_score = -1;

            for (auto& [c, candidates] : grouped_by_computer) {

                for (int group_size = 1;
                     group_size <= min(5, (int)candidates.size());
                     group_size++) {

                    vector<int> group(
                        candidates.begin(),
                        candidates.begin() + group_size
                    );

                    double spatial_bonus =
                        group_size * 10.0;

                    double min_arrival =
                        request_arrival_time[group[0]];

                    double max_arrival =
                        request_arrival_time[group[0]];

                    for (int rid : group) {
                        min_arrival =
                            min(min_arrival,
                                request_arrival_time[rid]);

                        max_arrival =
                            max(max_arrival,
                                request_arrival_time[rid]);
                    }

                    double time_variance =
                        max_arrival - min_arrival;

                    double temporal_score;

                    if (time_variance < 100)
                        temporal_score = -time_variance;
                    else
                        temporal_score = -time_variance * 10;

                    double total_score =
                        spatial_bonus + temporal_score;

                    if (total_score > best_score) {
                        best_score = total_score;
                        best_group = group;
                    }
                }
            }

            if (best_group.empty() ||
                best_group.size() < 2) {

                int count =
                    min((int)d_pre_ready.size(), 4);

                best_group.assign(
                    d_pre_ready.begin(),
                    d_pre_ready.begin() + count
                );
            }

            string assignment =
                "E D PRE -1 " +
                to_string(best_group.size());

            for (int rid : best_group)
                assignment += " " + to_string(rid);

            assignments.push_back(assignment);

            for (int rid : best_group) {
                request_state[rid].stage = "D_PROC_W";
                assigned_this_frame.insert(rid);
            }

            local_free = false;
        }

        // --------------------------------------------------
        // D_PROC
        // --------------------------------------------------

        for (int c = 0; c < K; c++) {

            vector<int> d_proc_ready;

            for (int rid : request_ids) {
                if (!request_state.count(rid))
                    continue;

                if (assigned_this_frame.count(rid))
                    continue;

                auto& state = request_state[rid];

                if (state.stage == "D_PROC_W" &&
                    state.computer == c &&
                    output_up_ready.count({
                        rid,
                        output_iter[rid]
                    })) {

                    d_proc_ready.push_back(rid);
                }
            }

            if (!d_proc_ready.empty() &&
                computer_free[c]) {

                int batch_size =
                    min((int)d_proc_ready.size(), 16);

                vector<int> batch(
                    d_proc_ready.begin(),
                    d_proc_ready.begin() + batch_size
                );

                string assignment =
                    "C" + to_string(c) +
                    " D PROC " +
                    to_string(c) +
                    " " +
                    to_string(batch.size());

                for (int rid : batch)
                    assignment += " " + to_string(rid);

                assignments.push_back(assignment);

                for (int rid : batch) {
                    request_state[rid].stage = "D_POST_W";
                    assigned_this_frame.insert(rid);
                }

                computer_free[c] = false;
            }
        }

        // --------------------------------------------------
        // D_POST
        // --------------------------------------------------

        vector<int> d_post_ready;

        for (int rid : request_ids) {
            if (!request_state.count(rid))
                continue;

            if (assigned_this_frame.count(rid))
                continue;

            auto& state = request_state[rid];

            if (state.stage == "D_POST_W" &&
                output_down_ready.count({
                    rid,
                    output_iter[rid]
                })) {

                d_post_ready.push_back(rid);
            }
        }

        if (!d_post_ready.empty() && local_free) {

            int batch_size =
                min((int)d_post_ready.size(), 16);

            vector<int> batch(
                d_post_ready.begin(),
                d_post_ready.begin() + batch_size
            );

            string assignment =
                "E D POST -1 " +
                to_string(batch.size());

            for (int rid : batch)
                assignment += " " + to_string(rid);

            assignments.push_back(assignment);

            for (int rid : batch) {
                output_iter[rid]++;
                request_state[rid].stage = "D_PRE";
                assigned_this_frame.insert(rid);
            }

            local_free = false;
        }

        // --------------------------------------------------
        // Output
        // --------------------------------------------------

        cout << assignments.size() << '\n';

        for (const string& assignment : assignments)
            cout << assignment << '\n';

        cout.flush();
    }

    return 0;
}