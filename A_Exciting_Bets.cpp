#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n,m;
        cin >> n >> m;

        if (n == m) {
            cout << "0 0\n";
            continue;
        }

        long long fun_max = abs(n - m);
        long long ans = min(n, m) % fun_max;
        long long op_min = min(ans, fun_max - ans);

        cout << fun_max << " " << op_min << "\n";
    }

    return 0;
}