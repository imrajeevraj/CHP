#include <bits/stdc++.h>
using namespace std;

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    if (n % 2) {
        cout << "NO\n";
        return;
    }

    int mn = 2000000007;
    int mx = -1;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            mn = min(mn, w[i]);
        else
            mx = max(mx, w[i]);
    }

    if (mx + 1 < mn)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}