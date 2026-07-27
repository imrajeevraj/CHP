#include <bits/stdc++.h>
using namespace std;

struct Element {
    int l, r, u, v;
};

void solve() {
    int n;
    cin >> n;

    vector<Element> a(n);
    for (auto &x : a)
        cin >> x.l >> x.r >> x.u >> x.v;

    for (int m = n; m >= 1; --m) {
        int j = 1;

        for (const auto &x : a) {
            if (j > m) break;

            int rightRank = m - j + 1;

            if ((j < x.l || j > x.r) &&
                (rightRank < x.u || rightRank > x.v))
                ++j;
        }

        if (j > m) {
            cout << m << '\n';
            return;
        }
    }

    cout << 0 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}