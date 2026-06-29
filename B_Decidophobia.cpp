#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, d;
        cin >> n >> d;

        vector<int64> a(n);

        for (int i = 0; i < n; i++)
            cin >> a[i];

        vector<int64> W(n);

        // W[0]
        int64 cur = 0;
        for (int i = 1; i <= d; i++) cur += a[i];
        for (int i = n - d; i < n; i++) cur += a[i];

        W[0] = cur;

        // Sliding window
        for (int i = 0; i < n - 1; i++) {
            cur -= a[(i - d + n) % n];
            cur -= a[(i + 1) % n];
            cur += a[i];
            cur += a[(i + d + 1) % n];
            W[i + 1] = cur;
        }

        int64 ans = 0;

        for (int i = 0; i < n; i++) {
            int64 gain = 2LL * d * a[i] - W[i];
            if (gain > 0) ans += gain;
        }

        cout << ans << '\n';
    }

    return 0;
}