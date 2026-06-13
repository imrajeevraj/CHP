#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mn = 1e9, mx = -1e9;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            mn = min(mn, x);
            mx = max(mx, x);
        }

        cout << (mx + 1 - mn) << '\n';
    }

    return 0;
}