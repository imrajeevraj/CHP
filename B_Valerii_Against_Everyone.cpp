#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        set<long long> s;
        bool ok = false;

        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;

            if (s.count(x))
                ok = true;

            s.insert(x);
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}