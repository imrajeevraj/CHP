#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    ll val;
    int idx;
};

bool cmp(Node a, Node b) {
    return a.val > b.val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<Node> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i].val;
            a[i].idx = i + 1;
        }

        sort(a.begin(), a.end(), cmp);

        vector<ll> pos(n + 1, 0);
        ll ans = 0;

        ll dist = 1;
        bool right = true;

        for (int i = 0; i < n; i++) {
            if (right) {
                pos[a[i].idx] = dist;
            } else {
                pos[a[i].idx] = -dist;
                dist++;
            }

            ans += 2LL * abs(pos[a[i].idx]) * a[i].val;
            right = !right;
        }

        cout << ans << "\n";
        cout << 0 << " ";

        for (int i = 1; i <= n; i++)
            cout << pos[i] << " ";

        cout << "\n";
    }

    return 0;
}