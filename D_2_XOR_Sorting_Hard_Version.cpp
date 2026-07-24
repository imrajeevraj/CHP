#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &u : a) cin >> u;

    int N = 1;
    while (N < n) N *= 2;
    while ((int)a.size() < N) a.push_back(1000000000); // sentinel, ties are fine

    int sz = N; // number of leaves
    vector<array<int, 3>> t(2 * sz);   // {min, max, k}
    vector<int> len(2 * sz, 1);

    for (int j = 0; j < sz; j++) t[sz + j] = {a[j], a[j], 0};

    auto pull = [&](int j, int l) {
        t[j][0] = min(t[j << 1][0], t[j << 1 | 1][0]);
        t[j][1] = max(t[j << 1][1], t[j << 1 | 1][1]);
        t[j][2] = max(t[j << 1][2], t[j << 1 | 1][2]);
        if (t[j << 1][1] > t[j << 1 | 1][0]) t[j][2] = max(t[j][2], l / 2);
    };

    for (int j = sz - 1; j >= 1; j--) {
        len[j] = 2 * len[j << 1];
        pull(j, len[j]);
    }

    cout << t[1][2] << "\n";

    while (q--) {
        int p, x;
        cin >> p >> x;
        p += sz;
        t[p] = {x, x, 0};
        p >>= 1;
        int l = 2;
        while (p) {
            pull(p, l);
            p >>= 1;
            l *= 2;
        }
        cout << t[1][2] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}