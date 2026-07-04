#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        long long w, h;
        cin >> w >> h;

        long long len_bottom, len_top, len_left, len_right;

        // Bottom side (y = 0)
        int k;
        cin >> k;
        vector<long long> xs(k);
        for (int i = 0; i < k; ++i) cin >> xs[i];
        len_bottom = xs.back() - xs.front();

        // Top side (y = h)
        cin >> k;
        xs.resize(k);
        for (int i = 0; i < k; ++i) cin >> xs[i];
        len_top = xs.back() - xs.front();

        // Left side (x = 0), coordinates are y's
        cin >> k;
        vector<long long> ys(k);
        for (int i = 0; i < k; ++i) cin >> ys[i];
        len_left = ys.back() - ys.front();

        // Right side (x = w), coordinates are y's
        cin >> k;
        ys.resize(k);
        for (int i = 0; i < k; ++i) cin >> ys[i];
        len_right = ys.back() - ys.front();

        long long ans = 0;
        ans = max(ans, len_bottom * h);
        ans = max(ans, len_top * h);
        ans = max(ans, len_left * w);
        ans = max(ans, len_right * w);

        cout << ans << '\n';
    }
    return 0;
}