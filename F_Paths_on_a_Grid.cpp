#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int P1 = 1000000007;
const int P2 = 1000000009;

// Fast modular exponentiation
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Modulo addition for double hashing
inline void add(pair<int, int>& a, const pair<int, int>& b) {
    a.first += b.first;
    if (a.first >= P1) a.first -= P1;
    a.second += b.second;
    if (a.second >= P2) a.second -= P2;
}

// Modulo multiplication for double hashing
inline pair<int, int> mul(const pair<int, int>& a, const pair<int, int>& b) {
    return {
        (int)((1LL * a.first * b.first) % P1),
        (int)((1LL * a.second * b.second) % P2)
    };
}

// Global RNG setup to ensure speed and low collision probability
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() ^ 0x123456789ABCDEFLL);
uniform_int_distribution<int> dist1(1, P1 - 1);
uniform_int_distribution<int> dist2(1, P2 - 1);

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // Assign random weights to right and down edges of each cell
    vector<pair<int, int>> W_r(n * m), W_d(n * m);
    for (int i = 0; i < n * m; ++i) {
        W_r[i] = {dist1(rng), dist2(rng)};
        W_d[i] = {dist1(rng), dist2(rng)};
    }

    // Forward DP: Hash of paths from (0, 0) to (i, j)
    vector<pair<int, int>> A(n * m, {0, 0});
    if (grid[0][0] == '1') A[0] = {1, 1};
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = i * m + j;
            if (grid[i][j] == '0') continue;
            
            if (i > 0 && grid[i-1][j] == '1') {
                add(A[u], mul(A[(i-1) * m + j], W_d[(i-1) * m + j]));
            }
            if (j > 0 && grid[i][j-1] == '1') {
                add(A[u], mul(A[i * m + j - 1], W_r[i * m + j - 1]));
            }
        }
    }

    // Backward DP: Hash of paths from (i, j) to (n-1, m-1)
    vector<pair<int, int>> B(n * m, {0, 0});
    if (grid[n-1][m-1] == '1') B[n * m - 1] = {1, 1};
    
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            int u = i * m + j;
            if (grid[i][j] == '0') continue;
            
            if (i + 1 < n && grid[i+1][j] == '1') {
                add(B[u], mul(B[(i+1) * m + j], W_d[u]));
            }
            if (j + 1 < m && grid[i][j+1] == '1') {
                add(B[u], mul(B[i * m + j + 1], W_r[u]));
            }
        }
    }

    // Collect and classify combined hashes
    int e_count = 0;
    vector<pair<int, int>> hashes;
    hashes.reserve(n * m);
    
    for (int u = 0; u < n * m; ++u) {
        pair<int, int> h = mul(A[u], B[u]);
        if (h.first == 0 && h.second == 0) {
            e_count++;
        } else {
            hashes.push_back(h);
        }
    }

    // Sort to easily count frequencies of identical non-zero hashes
    sort(hashes.begin(), hashes.end());
    
    // Add contributions to the total answer
    long long ans = (power(2, e_count) - 1 + MOD) % MOD;
    int sz = hashes.size();
    for (int i = 0; i < sz; ) {
        int j = i;
        while (j < sz && hashes[j] == hashes[i]) {
            j++;
        }
        int freq = j - i;
        ans = (ans + power(2, freq) - 1 + MOD) % MOD;
        i = j;
    }
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}