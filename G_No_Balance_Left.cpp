#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ull unsigned long long
 
const ll mx = 125'000;
const ll lim = mx * 2;
const ll bs = 402;
const ll inf = 1e9;
 
struct Bits {
    vector<ull> v;
 
    Bits(int n = 0) : v((n >> 6) + 1) {}
 
    bool get(int x) const {
        return v[x >> 6] >> (x & 63) & 1ULL;
    }
 
    bool set(int x) {
        ull bt = 1ULL << (x & 63);
        bool nw = !(v[x >> 6] & bt);
        v[x >> 6] |= bt;
        return nw;
    }
 
    ull word(int x) const {
        int i = x >> 6, sh = x & 63;
        ull z = v[i] >> sh;
        if (sh) z |= v[i + 1] << (64 - sh);
        return z;
    }
 
    ull merge(int i, ull x) {
        ull nw = x & ~v[i];
        v[i] |= x;
        return nw;
    }
};
 
struct Move {
    int r, d;
};
 
Bits get_rep(const vector<int> &c, int mn) {
    Bits rep(lim);
    Bits coin(mx);
    for (int x : c) coin.set(x);
 
    vector<pair<int, ull>> nz;
    nz.reserve(2'006);
    for (int i = 0; i < (int)coin.v.size(); ++i)
        if (coin.v[i]) nz.push_back({i, coin.v[i]});
 
    rep.set(0);
    for (int x = 0; x + mn <= lim; ++x) {
        if (!rep.get(x)) continue;
 
        int ws = x >> 6, sh = x & 63;
        for (auto [i, bt] : nz) {
            int j = i + ws;
            if (j < (int)rep.v.size()) rep.v[j] |= bt << sh;
            if (sh && j + 1 < (int)rep.v.size())
                rep.v[j + 1] |= bt >> (64 - sh);
        }
    }
 
    return rep;
}
 
vector<Move> moves(const Bits &rep, const vector<int> &a,
                   const vector<int> &b) {
    vector<int> rq(lim + mx + 1, inf);
    int j = -1;
 
    for (int x = 1; x <= lim; ++x) {
        if (!rep.get(x)) continue;
        while (j + 1 < (int)a.size() && a[j + 1] <= x) ++j;
 
        int r = (j < 0 ? 0 : b[j]);
        int d = x - r;
        if (d) rq[d + mx] = min(rq[d + mx], r);
    }
 
    vector<Move> e;
    for (int i = 0; i < (int)rq.size(); ++i)
        if (rq[i] != inf) e.push_back({rq[i], (int)(i - mx)});
 
    sort(e.begin(), e.end(), [](Move x, Move y) {
        return x.r < y.r;
    });
    return e;
}
 
Bits walk(const vector<Move> &e) {
    int nb = e.size() / bs;
    vector<Bits> pre(nb + 1, Bits(2 * lim + 64));
 
    for (int k = 1; k <= nb; ++k) {
        pre[k] = pre[k - 1];
        for (int i = (k - 1) * bs; i < k * bs; ++i)
            pre[k].set(e[i].d + lim);
    }
 
    Bits good(lim);
    vector<int> q{0};
    good.set(0);
 
    auto push = [&](int x) {
        if (x >= 0 && x <= lim && good.set(x)) q.push_back(x);
    };
 
    for (int z = 0; z < (int)q.size(); ++z) {
        int v = q[z];
        int cnt = upper_bound(e.begin(), e.end(), v, [](int x, Move y) {
            return x < y.r;
        }) - e.begin();
        int bl = cnt / bs;
 
        for (int w = 0; w < (int)good.v.size(); ++w) {
            int h = w << 6;
            ull x = pre[bl].word(lim + h - v);
            if (h + 63 > lim) x &= (1ULL << (lim - h + 1)) - 1;
 
            ull nw = good.merge(w, x);
            while (nw) {
                int bt = __builtin_ctzll(nw);
                q.push_back(h + bt);
                nw &= nw - 1;
            }
        }
 
        for (int i = bl * bs; i < cnt; ++i) push(v + e[i].d);
    }
 
    return good;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m, s;
    cin >> n >> m >> s;
 
    vector<int> c(n), a(m), b(m);
    for (int &x : c) cin >> x;
    for (int i = 0; i < m; ++i) cin >> a[i] >> b[i];
 
    int mn = *min_element(c.begin(), c.end());
    if (mn >= a[0]) {
        for (int h = 1; h <= s; ++h) cout << "NO\n";
        return 0;
    }
 
    Bits rep = get_rep(c, mn);
    vector<Move> e = moves(rep, a, b);
    Bits good = walk(e);
 
    for (int h = 1; h <= s; ++h)
        cout << (good.get(h) ? "YES\n" : "NO\n");
 
    return 0;
}