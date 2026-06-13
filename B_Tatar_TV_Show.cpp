#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;

        vector<int> parity(k, 0);

        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                parity[i % k] ^= 1;
            }
        }

        bool ok = true;
        for (int r = 0; r < k; r++) {
            if (parity[r]) {
                ok = false;
                break;
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}