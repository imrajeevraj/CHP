#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        long long n, k, b;
        long long s;
        cin >> n >> k >> b >> s;

        long long minimum = b * k;
        long long maximum = b * k + n * (k - 1);

        if (s < minimum || s > maximum) {
            cout << -1 << '\n';
            continue;
        }

        vector<long long> a(n, 0);
        a[0] = b * k;
        long long rem = s - a[0];

        long long add = min(rem, k - 1);
        a[0] += add;
        rem -= add;

        for (int i = 1; i < n; i++) {
            long long cur = min(rem, k - 1);
            a[i] = cur;
            rem -= cur;
        }

        for (int i = 0; i < n; i++) {
            cout << a[i] << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}