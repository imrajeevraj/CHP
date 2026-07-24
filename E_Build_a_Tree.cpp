#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    long long n, k;
    cin >> n >> k;
    
    long long min_k = 2LL * (n - 1);
    long long max_k = 2LL * ((n * n) / 4);
    
    // k must be between the minimum and maximum limits and must be even
    if (k % 2 != 0 || k < min_k || k > max_k) {
        cout << -1 << "\n";
        return        ;
    }
 
    // R is the remaining number of components we need to add to reach our target k
    long long R = (k - min_k) / 2;
    vector<int> P(n + 1, 1);
    
    for (int i = 4; i <= n; i++) {
        if (R > 0) {
            // Maximum depth increase we can extract from vertex i
            long long M = i / 2 - 1;
            long long add = min(R, M);
            R -= add;
            long long d = add;
            
            if (d == 0) {
                P[i] = 1;
            } else {
                // Attach to the appropriate chain based on parity
                if (i % 2 == 0) {
                    P[i] = 2 * d;
                } else {
                    P[i] = 2 * d + 1;
                }
            }
        } else {
            P[i] = 1;
        }
    }
    
    // Print the n - 1 edges
    for (int i =    2; i <= n; i++) {
        cout << P[i] << " " << i << "\n";
    }
}
 
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}