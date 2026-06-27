#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> s(n), p(n);
        for (int i = 0; i < n; i++) cin >> s[i];

        bool ok = true;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;

            if (j - i == 1) {
                ok = false;
                break;
            }

            for (int k = i; k < j - 1; k++) {
                p[k] = k + 2;
            }
            p[j - 1] = i + 1;

            i = j;
        }

        if (!ok) {
            cout << -1 << '\n';
        } else {
            for (int k = 0; k < n; k++) {
                cout << p[k] << " \n"[k == n - 1];
            }
        }
    }

    return 0;
}