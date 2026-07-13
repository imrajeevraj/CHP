#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long a, b;
        cin >> a >> b;

        long long ans = 1e18;

        for (int add = 0; add <= 35; add++) {
            if (b + add == 1) continue;

            long long curB = b + add;
            long long temp = a;
            long long ops = add;

            while (temp > 0) {
                temp /= curB;
                ops++;
            }

            ans = min(ans, ops);
        }

        cout << ans << '\n';
    }

    return 0;
}