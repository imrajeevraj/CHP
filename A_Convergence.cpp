#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    int ans = n;
    for (int i = 0; i < n; i++) {
        auto it1 = lower_bound(a.begin(), a.end(), a[i]);
        int L = distance(a.begin(), it1);
        
        auto it2 = upper_bound(a.begin(), a.end(), a[i]);
        int R = distance(it2, a.end());
        
        int cost = max(L, R);
        ans = min(ans, cost);
    }
    
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

