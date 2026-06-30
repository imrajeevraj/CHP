#include <bits/stdc++.h>
using namespace std;

bool good(long long x) {
    bool vis[10] = {};
    int cnt = 0;

    while (x) {
        int d = x % 10;
        if (!vis[d]) {
            vis[d] = true;
            cnt++;
            if (cnt > 2) return false;
        }
        x /= 10;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long x;
        cin >> x;

        for (int y = 2; y <= 99; y++) {
            if (good(y) && good(x * 1LL * y)) {
                cout << y << '\n';
                break;
            }
        }
    }
}