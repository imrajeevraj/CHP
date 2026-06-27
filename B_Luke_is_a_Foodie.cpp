#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long x;
        cin >> n >> x;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long L = a[0] - x;
        long long R = a[0] + x;
        int ans = 0;

        for (int i = 1; i < n; i++) {
            long long nl = max(L, a[i] - x);
            long long nr = min(R, a[i] + x);

            if (nl > nr) {
                ans++;
                L = a[i] - x;
                R = a[i] + x;
            } else {
                L = nl;
                R = nr;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}