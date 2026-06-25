#include <bits/stdc++.h>
using namespace std;

int main() {

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        multiset<long long> s;

        for (int i = 0; i < n; ++i) {
            long long x = a[i];
            s.insert(x);

            while (true) {
                auto it = prev(s.end());
                long long mx = *it;
                if (mx <= x) break;
                s.erase(it);
                x += mx;
                s.insert(x);
            }
        }

        long long ans = 0;
        for (long long v : s) ans = max(ans, v);
        cout << ans << '\n';
    }
    return 0;
}