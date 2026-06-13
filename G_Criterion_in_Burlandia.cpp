#include <bits/stdc++.h>
using namespace std;

static const int LOG = 20;

struct HLD {
    int n, timer;
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, pos, sz, rin;
    vector<int> val;

    HLD(int n) : n(n) {
        g.assign(n + 1, {});
        parent.assign(n + 1, 0);
        depth.assign(n + 1, 0);
        heavy.assign(n + 1, -1);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        rin.assign(n + 1, 0);
        val.assign(n + 1, 0);
        timer = 0;
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dfs(int v, int p) {
        parent[v] = p;
        sz[v] = 1;
        int mx = 0;
        for (int to : g[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            int sub = dfs(to, v);
            sz[v] += sub;
            if (sub > mx) {
                mx = sub;
                heavy[v] = to;
            }
        }
        return sz[v];
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = timer;
        rin[timer] = v;
        timer++;
        if (heavy[v] != -1) decompose(heavy[v], h);
        for (int to : g[v]) {
            if (to == parent[v] || to == heavy[v]) continue;
            decompose(to, to);
        }
    }

    void build() {
        dfs(1, 0);
        decompose(1, 1);
    }

    vector<pair<int,int>> getPathSegments(int u, int v) {
        vector<pair<int,int>> up, down;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                up.push_back({pos[head[u]], pos[u]});
                u = parent[head[u]];
            } else {
                down.push_back({pos[head[v]], pos[v]});
                v = parent[head[v]];
            }
        }
        if (depth[u] > depth[v]) up.push_back({pos[v], pos[u]});
        else down.push_back({pos[u], pos[v]});

        vector<pair<int,int>> res;
        for (auto &seg : up) res.push_back({seg.second, seg.first}); // reversed direction
        reverse(down.begin(), down.end());
        for (auto &seg : down) res.push_back(seg); // normal direction
        return res;
    }
};

long long countValidOnPathValues(const vector<int>& a) {
    int m = (int)a.size();
    long long ans = 0;
    int mask = 0, l = 0;
    for (int r = 0; r < m; r++) {
        while ((mask & a[r]) != 0) {
            mask ^= a[l];
            l++;
        }
        mask |= a[r];
        ans += (r - l + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;

        HLD hld(n);
        for (int i = 1; i <= n; i++) cin >> hld.val[i];

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            hld.addEdge(u, v);
        }

        hld.build();

        vector<int> base(n);
        for (int i = 1; i <= n; i++) {
            base[hld.pos[i]] = hld.val[i];
        }

        while (q--) {
            int x, y;
            cin >> x >> y;

            auto segs = hld.getPathSegments(x, y);
            vector<int> pathVals;
            for (auto [l, r] : segs) {
                if (l <= r) {
                    for (int i = l; i <= r; i++) pathVals.push_back(base[i]);
                } else {
                    for (int i = l; i >= r; i--) pathVals.push_back(base[i]);
                }
            }

            cout << countValidOnPathValues(pathVals) << '\n';
        }
    }
    return 0;
}