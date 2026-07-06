#include <bits/stdc++.h>
using namespace std;

namespace Milkcat {
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 2e6 + 5, M = 2e5 + 5;
    int n, m, rs, d, p, q, l[N], r[N], c[M];
    bitset<M> f;

    int val(int x) {
        x -= d;
        return (x >= 0 && x <= m ? f[x] : 0);
    }

    int main() {
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> l[i] >> r[i], m = max(m, r[i]);
        for (int i = 1; i <= n; ++i) {
            if (!l[i]) d = min(d + r[i], (int)1e9);
            else d = min(d + l[i] - 1, (int)1e9), c[r[i] - l[i] + 1]++;
        }
        f = 1;
        for (int i = 1; i <= m; ++i) {
            if (i * 2 <= m) c[i * 2] += c[i] >> 1;
            if (c[i] & 1) f ^= (f << i);
        }
        for (int i = 2; i <= m; ++i) f[i] = f[i] ^ f[i - 2];
        for (int i = 1; i <= n; ++i) {
            if (!l[i]) rs ^= val(r[i] * 2 - 2), p ^= r[i] & 1;
            else rs ^= val(l[i] + r[i] - 1 - 2), q += ((l[i] & 1) == (r[i] & 1) ? 1 : 2);
        }
        cout << (rs ^ (!q ? !p : (q < 2))) << '\n';
        for (int i = 1; i <= m; ++i) c[i] = 0;
        m = rs = d = p = q = 0;
        return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) Milkcat::main();
    return 0;
}