#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            cnt[x]++;
        }

        int mx = 0, distinct = 0;
        for (int v = 1; v <= n; ++v) {
            if (cnt[v] > 0) {
                distinct++;
                mx = max(mx, cnt[v]);
            }
        }

        if (mx % 2 == 0) {
            cout << "NO\n";
        } else if (distinct == 1) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}