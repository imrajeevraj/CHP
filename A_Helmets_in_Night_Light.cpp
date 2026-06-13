#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;

    while (t--) {
        long long n, p;
        cin >> n >> p;

        vector<long long> a(n), b(n);

        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        vector<pair<long long, long long>> v;

        for (int i = 0; i < n; i++) {
            v.push_back({b[i], a[i]}); // {cost, capacity}
        }

        sort(v.begin(), v.end());

        long long ans = p;      // inform one person directly
        long long informed = 1; // one person already knows

        for (int i = 0; i < n; i++) {
            long long cost = v[i].first;
            long long cap = v[i].second;

            if (informed == n) break;

            if (cost >= p) break;

            long long canUse = min(cap, n - informed);

            ans += canUse * cost;
            informed += canUse;
        }

        ans += (n - informed) * p;

        cout << ans << '\n';
    }

    return 0;
}