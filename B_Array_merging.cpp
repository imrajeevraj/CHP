#include <bits/stdc++.h>
using namespace std;

void processRuns(const vector<int>& v, vector<int>& best) {
    int n = (int)v.size();
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && v[j] == v[i]) j++;
        best[v[i]] = max(best[v[i]], j - i);
        i = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        vector<int> bestA(2 * n + 1, 0), bestB(2 * n + 1, 0);

        processRuns(a, bestA);
        processRuns(b, bestB);

        int ans = 0;
        for (int x = 1; x <= 2 * n; x++) {
            ans = max(ans, bestA[x] + bestB[x]);
        }

        cout << ans << '\n';
    }

    return 0;
}