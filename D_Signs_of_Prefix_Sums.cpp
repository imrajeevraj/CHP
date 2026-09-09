#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int n, const string& s, int K) {
    int L = 0, R = 0;
    for (int i = 0; i < n; ++i) {
        int nL = L - K;
        int nR = R + K;
        
        if (s[i] == '+') {
            nL = max(nL, 1);
            if (L == R && L >= 1 && L <= R) {
            }
        } else if (s[i] == '-') {
            nR = min(nR, -1);
        } else {
            nL = max(nL, 0);
            nR = min(nR, 0);
            if (L == 0 && R == 0) return false;
        }

        if (nL > nR) return false;
        L = nL;
        R = nR;
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (s[0] == '0') {
        cout << -1 << "\n";
        return;
    }
    for (int i = 0; i + 1 < n; ++i) {
        if (s[i] == '0' && s[i + 1] == '0') {
            cout << -1 << "\n";
            return;
        }
    }

    int low = 1, high = n + 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(n, s, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}