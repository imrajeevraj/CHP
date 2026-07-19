#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        long long n, k, m;
        cin >> n >> k >> m;

        if (m < k) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        long long prevT = 0;
        for (long long i = 1; i <= n; i++) {
            long long q = i / k;
            long long rem = i % k;
            long long T = q * m + rem;
            long long a = T - prevT;
            cout << a;
            if (i < n) cout << ' ';
            prevT = T;
        }
        cout << '\n';
    }
    return 0;
}