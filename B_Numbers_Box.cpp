#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        long long sum = 0;
        int neg = 0;
        int mn = INT_MAX;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int x;
                cin >> x;

                if (x < 0)
                    neg++;

                sum += abs(x);
                mn = min(mn, abs(x));
            }
        }

        if (neg % 2)
            sum -= 2LL * mn;

        cout << sum << "\n";
    }

    return 0;
}