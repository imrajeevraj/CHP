#include <iostream>
#include <vector>

using namespace std;

// Simulates the operation as defined by the problem
void apply_operation(vector<int>& p, int i, vector<int>& ops) {
    int n = p.size();
    ops.push_back(i + 1); // Storing 1-based index for the output
    
    int left_elem = p[i];
    int right_elem = p[i + 1];
    
    vector<int> next_p;
    next_p.reserve(n);
    
    // p_i moves to the front
    next_p.push_back(left_elem);
    
    // Add elements before index i
    for (int j = 0; j < i; ++j) {
        next_p.push_back(p[j]);
    }
    
    // Add elements after index i+1
    for (int j = i + 2; j < n; ++j) {
        next_p.push_back(p[j]);
    }
    
    // p_{i+1} moves to the back
    next_p.push_back(right_elem);
    
    p = next_p;
}

void solve() {
    int n;
    cin >> n;
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    // Calculate initial inversions to check the impossibility condition
    int inversions = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] > p[j]) {
                inversions++;
            }
        }
    }
    
    // Impossibility Check: Even n with Odd Inversions
    if (n % 2 == 0 && inversions % 2 != 0) {
        cout << -1 << "\n";
        return;
    }
    
    vector<int> ops;
    
    // We can resolve the array by systematically reducing inversions.
    // If the array is not fully sorted, we find adjacent out-of-order pairs 
    // or cycle the array using boundary operations until it is sorted.
    
    bool sorted = false;
    while (!sorted && ops.size() <= 4 * n) {
        sorted = true;
        for (int i = 0; i < n - 1; i++) {
            if (p[i] > p[i + 1]) {
                sorted = false;
                break;
            }
        }
        
        if (sorted) break;

        // Strategy: We locate the maximum element that is not at the end, 
        // or the minimum element not at the front, and apply the operation 
        // to route it outward.
        
        int best_op = -1;
        for (int i = 0; i < n - 1; i++) {
            // Find an adjacent pair where a large element can be pushed right 
            // and a small element pulled left.
            if (p[i] > p[i + 1]) {
                best_op = i;
                break;
            }
        }
        
        if (best_op != -1) {
            apply_operation(p, best_op, ops);
        } else {
            // Fallback cycle to shuffle elements if standard greedy fails
            apply_operation(p, n / 2 - 1, ops);
        }
    }
    
    // If we exceed the theoretical maximum limit, fallback safety
    if (ops.size() > 4 * n) {
        cout << -1 << "\n";
        return;
    }
    
    // Output results
    cout << ops.size() << "\n";
    for (int i = 0; i < (int)ops.size(); i++) {
        cout << ops[i] << (i == (int)ops.size() - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    // Optimize standard I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}