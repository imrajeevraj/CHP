#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    int blocks = n - k;

    if (blocks < 2) {
        cout << -1 << '\n';
        return;
    }

    int ones = (n + 1) / 2;
    int zeros = n / 2;

    int oneBlocks = (blocks + 1) / 2;
    int zeroBlocks = blocks / 2;

    string ans;

    ans += string(ones - oneBlocks + 1, '1');

   
    ans += string(zeros - zeroBlocks + 1, '0');

    for (int i = 2; i < blocks; i++) {
        ans += (i % 2 == 0) ? '1' : '0';
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}