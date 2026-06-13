#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;

    while (t--) {
        long long n, k;
        cin >> n >> k;

        vector<long long> a(n * k);
        for (long long &x : a)
            cin >> x;

        long long step = n / 2 + 1;
        long long idx = n * k - step;
        long long ans = 0;

        for (int i = 0; i < k; i++) {
            ans += a[idx];
            idx -= step;
        }

        cout << ans << '\n';
    }

    return 0;
}