#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    int mx = 0;

    for (int i = 1; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    if (mx != n - 1) {
        cout << 0 << '\n';
        return;
    }

    int L = -1, R = -1;

    for (int i = 1; i < n; i++) {
        if (a[i] == n - 1) {
            if (L == -1) L = i;
            R = i;
        }
    }

    for (int i = 1; i < L; i++) {
        if (a[i] > a[i + 1]) {
            cout << 0 << '\n';
            return;
        }
    }

    for (int i = R; i < n - 1; i++) {
        if (a[i] < a[i + 1]) {
            cout << 0 << '\n';
            return;
        }
    }

    int l = L, r = R;
    int U = L, V = R + 1;
    long long ans = 2;
    int cnt = 2;

    for (int x = n - 2; x >= 1; x--) {
        while (l > 1 && a[l - 1] >= x) --l;
        while (r < n - 1 && a[r + 1] >= x) ++r;

        bool left = l < U;
        bool right = r >= V;

        if (left && right) {
            cout << 0 << '\n';
            return;
        }

        if (left) {
            U = l;
        } else if (right) {
            V = r + 1;
        } else {
            int freePos = V - U + 1 - cnt;
            if (freePos <= 0) {
                cout << 0 << '\n';
                return;
            }
            ans = ans * freePos % MOD;
        }

        cnt++;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) solve();

    return 0;
}