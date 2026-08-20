#include <bits/stdc++.h>
using namespace std;

struct RequestState {
    string stage;
    int c;
    int Lin;
};

// custom hash for pair
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

using MinHeap = priority_queue<int, vector<int>, greater<int>>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    if (!getline(cin, line)) return 0;
    stringstream ss1(line);
    int K;
    double S, latency_in_ms, bandwidth_gbps, bytes_per_token;
    int num_layers;
    ss1 >> K >> S >> latency_in_ms >> bandwidth_gbps >> bytes_per_token >> num_layers;

    if (!getline(cin, line)) return 0;
    stringstream ss2(line);
    double SLO1, SLO2, tp_ub, tp_base, dist_base, w_tp, w_c;
    ss2 >> SLO1 >> SLO2 >> tp_ub >> tp_base >> dist_base >> w_tp >> w_c;

    if (!getline(cin, line)) return 0;
    stringstream ss3(line);
    int N;
    ss3 >> N;

    vector<vector<double>> task_table(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, line);
        stringstream ss(line);
        double val;
        while (ss >> val) {
            task_table[i].push_back(val);
        }
    }

    unordered_map<int, RequestState> request_state;
    unordered_map<int, double> request_arrival_time;
    unordered_map<int, int> output_iter;

    vector<bool> computer_free(K, true);
    vector<int> computer_request_count(K, 0);
    bool local_free = true;

    unordered_set<int> input_up_ready;
    unordered_set<int> input_down_ready;
    unordered_set<pair<int, int>, pair_hash> output_up_ready;
    unordered_set<pair<int, int>, pair_hash> output_down_ready;

    MinHeap p_pre_heap;
    vector<MinHeap> p_proc_heaps(K);
    vector<MinHeap> d_pre_heaps(K);
    vector<MinHeap> d_proc_heaps(K);
    MinHeap d_pre_global;
    MinHeap d_post_heap;

    auto valid = [&](int rid, const string& stage) {
        auto it = request_state.find(rid);
        return it != request_state.end() && it->second.stage == stage;
    };

    auto clean_heap = [&](MinHeap& heap, const string& stage) {
        while (!heap.empty()) {
            int rid = heap.top();
            if (valid(rid, stage)) {
                break;
            }
            heap.pop();
        }
    };

    auto peek_valid = [&](MinHeap& heap, const string& stage, int limit) {
        vector<int> result;
        while (!heap.empty() && result.size() < (size_t)limit) {
            int rid = heap.top();
            heap.pop();
            if (valid(rid, stage)) {
                result.push_back(rid);
            }
        }
        for (int rid : result) {
            heap.push(rid);
        }
        return result;
    };

    auto add_p_proc = [&](int rid) {
        auto it = request_state.find(rid);
        if (it != request_state.end() && it->second.stage == "P_PROC") {
            p_proc_heaps[it->second.c].push(rid);
        }
    };

    auto add_d_pre = [&](int rid) {
        auto it = request_state.find(rid);
        if (it != request_state.end() && it->second.stage == "D_PRE") {
            int c = it->second.c;
            if (c >= 0 && c < K) d_pre_heaps[c].push(rid);
            d_pre_global.push(rid);
        }
    };

    auto add_d_proc = [&](int rid) {
        auto it = request_state.find(rid);
        if (it != request_state.end() && it->second.stage == "D_PROC_W") {
            int c = it->second.c;
            if (output_up_ready.count({rid, output_iter[rid]})) {
                if (c >= 0 && c < K) d_proc_heaps[c].push(rid);
            }
        }
    };

    auto add_d_post = [&](int rid) {
        auto it = request_state.find(rid);
        if (it != request_state.end() && it->second.stage == "D_POST_W") {
            if (output_down_ready.count({rid, output_iter[rid]})) {
                d_post_heap.push(rid);
            }
        }
    };

    while (true) {
        if (!getline(cin, line)) break;
        
        // Trim whitespace/carriage returns
        size_t end = line.find_last_not_of(" \r\n\t");
        if (end != string::npos) {
            line = line.substr(0, end + 1);
        } else {
            line = "";
        }

        if (line.empty()) continue; // skip blank lines if any, to match strip() behavior when robust
        if (line == "END") break;

        double timestamp = stod(line);
        
        if (!getline(cin, line)) break;
        stringstream ss_num(line);
        int num_events;
        ss_num >> num_events;


        unordered_set<int> assigned_this_frame;

        for (int i = 0; i < num_events; ++i) {
            getline(cin, line);
            stringstream ss(line);
            string event_type;
            ss >> event_type;

            if (event_type == "ARR") {
                int rid, Lin;
                ss >> rid >> Lin;
                request_state[rid] = {"P_PRE", -1, Lin};
                request_arrival_time[rid] = timestamp;
                output_iter[rid] = 0;
                p_pre_heap.push(rid);
            } else if (event_type == "TDN") {
                string server;
                ss >> server;
                if (server == "E") {
                    local_free = true;
                } else {
                    try {
                        int comp_id;
                        if (server[0] == 'C') {
                            comp_id = stoi(server.substr(1));
                        } else {
                            comp_id = stoi(server);
                        }
                        if (comp_id >= 0 && comp_id < K) {
                            computer_free[comp_id] = true;
                        }
                    } catch (...) {}
                }
            } else if (event_type == "XDN") {
                string direction;
                ss >> direction;
                
                vector<string> tokens;
                string t;
                while (ss >> t) {
                    tokens.push_back(t);
                }
                
                if (tokens.size() < 5) continue;
                
                string phase = tokens[2];
                vector<int> rids;
                for (size_t j = 4; j < tokens.size(); ++j) {
                    rids.push_back(stoi(tokens[j]));
                }

                if (direction == "UP") {
                    if (phase == "PRE") {
                        for (int rid : rids) {
                            input_up_ready.insert(rid);
                            add_p_proc(rid);
                        }
                    } else if (phase == "DEC") {
                        for (int rid : rids) {
                            output_up_ready.insert({rid, output_iter[rid]});
                            add_d_proc(rid);
                        }
                    }
                } else if (direction == "DOWN") {
                    if (phase == "PRE") {
                        for (int rid : rids) {
                            input_down_ready.insert(rid);
                        }
                    } else if (phase == "DEC") {
                        for (int rid : rids) {
                            output_down_ready.insert({rid, output_iter[rid]});
                            add_d_post(rid);
                        }
                    }
                }
            } else if (event_type == "FIN") {
                int rid;
                ss >> rid;
                auto it = request_state.find(rid);
                if (it != request_state.end()) {
                    int c = it->second.c;
                    if (c >= 0 && c < K) {
                        computer_request_count[c]--;
                    }
                    request_state.erase(it);
                }
                output_iter.erase(rid);
                request_arrival_time.erase(rid);
            }
        }

        vector<string> assignments;

        // 1. D POST (highest priority for local)
        if (local_free) {
            clean_heap(d_post_heap, "D_POST_W");
            if (!d_post_heap.empty()) {
                vector<int> batch;
                while (!d_post_heap.empty() && batch.size() < 64) {
                    int rid = d_post_heap.top();
                    d_post_heap.pop();
                    auto it = request_state.find(rid);
                    if (it != request_state.end() && it->second.stage == "D_POST_W" && output_down_ready.count({rid, output_iter[rid]})) {
                        batch.push_back(rid);
                    }
                }
                if (!batch.empty()) {
                    string assign = "E D POST -1 " + to_string(batch.size());
                    for (int rid : batch) assign += " " + to_string(rid);
                    assignments.push_back(assign);
                    
                    for (int rid : batch) {
                        auto it = request_state.find(rid);
                        if (it != request_state.end()) {
                            output_iter[rid]++;
                            it->second.stage = "D_PRE";
                            assigned_this_frame.insert(rid);
                            add_d_pre(rid);
                        }
                    }
                    local_free = false;
                }
            }
        }

        // 2. D PRE (second priority for local)
        if (local_free) {
            vector<int> best_group;
            double best_score = -1;

            for (int c = 0; c < K; ++c) {
                vector<int> candidates = peek_valid(d_pre_heaps[c], "D_PRE", 64);
                if (candidates.empty()) continue;
                
                int max_group = min(64, (int)candidates.size());
                
                for (int group_size = 1; group_size <= max_group; ++group_size) {
                    vector<int> group(candidates.begin(), candidates.begin() + group_size);
                    double min_arr = request_arrival_time[group[0]];
                    double max_arr = min_arr;
                    for (int rid : group) {
                        min_arr = min(min_arr, request_arrival_time[rid]);
                        max_arr = max(max_arr, request_arrival_time[rid]);
                    }
                    
                    double time_variance = group.empty() ? 0 : (max_arr - min_arr);
                    double spatial_bonus = group_size * 10;
                    double temporal_score = (time_variance < 100) ? -time_variance : -time_variance * 10;
                    double total_score = spatial_bonus + temporal_score;
                    
                    if (total_score > best_score) {
                        best_score = total_score;
                        best_group = group;
                    }
                }
            }

            if (best_group.size() < 2) {
                best_group = peek_valid(d_pre_global, "D_PRE", 64);
            }

            if (!best_group.empty()) {
                string assign = "E D PRE -1 " + to_string(best_group.size());
                for (int rid : best_group) assign += " " + to_string(rid);
                assignments.push_back(assign);
                
                for (int rid : best_group) {
                    auto it = request_state.find(rid);
                    if (it != request_state.end() && it->second.stage == "D_PRE") {
                        it->second.stage = "D_PROC_W";
                        assigned_this_frame.insert(rid);
                        add_d_proc(rid);
                    }
                }
                local_free = false;
            }
        }

        // 3. P POST (third priority for local)
        if (local_free) {
            int best_rid = -1;
            for (const auto& kv : request_state) {
                int rid = kv.first;
                const auto& state = kv.second;
                if (!assigned_this_frame.count(rid) && state.stage == "P_POST" && input_down_ready.count(rid)) {
                    if (best_rid == -1 || rid < best_rid) {
                        best_rid = rid;
                    }
                }
            }
            if (best_rid != -1) {
                int rid = best_rid;
                auto& state = request_state[rid];
                assignments.push_back("E P POST " + to_string(state.c) + " " + to_string(rid));
                state.stage = "D_PRE";
                local_free = false;
                assigned_this_frame.insert(rid);
                add_d_pre(rid);
            }
        }

        // 4. P PRE (lowest priority for local)
        if (local_free && !p_pre_heap.empty() && K > 0) {
            clean_heap(p_pre_heap, "P_PRE");
            if (!p_pre_heap.empty()) {
                int rid = p_pre_heap.top();
                p_pre_heap.pop();
                
                auto it = request_state.find(rid);
                if (it != request_state.end() && it->second.stage == "P_PRE") {
                    int min_load = computer_request_count[0];
                    for (int comp = 1; comp < K; ++comp) {
                        if (computer_request_count[comp] < min_load) {
                            min_load = computer_request_count[comp];
                        }
                    }
                    
                    int c = -1;
                    for (int comp = 0; comp < K; ++comp) {
                        if (computer_free[comp] && computer_request_count[comp] == min_load) {
                            c = comp;
                            break;
                        }
                    }
                    if (c == -1) {
                        for (int comp = 0; comp < K; ++comp) {
                            if (computer_request_count[comp] == min_load) {
                                c = comp;
                                break;
                            }
                        }
                    }
                    if (c == -1) c = 0;
                    
                    assignments.push_back("E P PRE " + to_string(c) + " " + to_string(rid));
                    it->second.stage = "P_PROC";
                    it->second.c = c;
                    
                    computer_request_count[c]++;
                    local_free = false;
                    assigned_this_frame.insert(rid);
                    
                    if (input_up_ready.count(rid)) {
                        p_proc_heaps[c].push(rid);
                    }
                }
            }
        }

        // Remote tasks
        for (int c = 0; c < K; ++c) {
            if (!computer_free[c]) continue;
            
            clean_heap(p_proc_heaps[c], "P_PROC");
            if (p_proc_heaps[c].empty()) continue;
            
            int rid = p_proc_heaps[c].top();
            p_proc_heaps[c].pop();
            
            auto it = request_state.find(rid);
            if (it == request_state.end() || it->second.stage != "P_PROC") continue;
            
            assignments.push_back("C" + to_string(c) + " P PROC 0 " + to_string(num_layers) + " " + to_string(c) + " " + to_string(rid));
            
            computer_free[c] = false;
            it->second.stage = "P_POST";
            assigned_this_frame.insert(rid);
        }

        for (int c = 0; c < K; ++c) {
            if (!computer_free[c]) continue;
            
            clean_heap(d_proc_heaps[c], "D_PROC_W");
            if (d_proc_heaps[c].empty()) continue;
            
            vector<int> batch;
            while (!d_proc_heaps[c].empty() && batch.size() < 64) {
                int rid = d_proc_heaps[c].top();
                d_proc_heaps[c].pop();
                auto it = request_state.find(rid);
                if (it != request_state.end() && it->second.stage == "D_PROC_W" && output_up_ready.count({rid, output_iter[rid]})) {
                    batch.push_back(rid);
                }
            }
            if (batch.empty()) continue;
            
            string assign = "C" + to_string(c) + " D PROC " + to_string(c) + " " + to_string(batch.size());
            for (int rid : batch) assign += " " + to_string(rid);
            assignments.push_back(assign);
            
            for (int rid : batch) {
                auto it = request_state.find(rid);
                if (it != request_state.end()) {
                    it->second.stage = "D_POST_W";
                    assigned_this_frame.insert(rid);
                    add_d_post(rid);
                }
            }
            computer_free[c] = false;
        }

        cout << assignments.size() << "\n";
        for (const string& assign : assignments) {
            cout << assign << "\n";
        }
        cout << flush;
    }

    return 0;
}
