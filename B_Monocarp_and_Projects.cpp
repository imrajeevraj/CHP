#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long x, y, k;
    cin >> x >> y >> k;

    long long d = y - x;
    long long L = x;
    long long R = x + k - 1;

    long long ans = 0;

    // Part 1: a <= d
    long long right_bound = min(R, d);
    for (long long a = L; a <= right_bound; ++a) {
        ans += (d % a);
    }

    // Part 2: a > d
    long long left_bound = max(L, d + 1);
    if (left_bound <= R) {
        ans += (R - left_bound + 1) * d;
    }

    cout << ans << "\n";
}

int main() {

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}