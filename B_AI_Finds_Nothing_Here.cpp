#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long power(long long a, long long b) {
    long long res = 1;
    a %= MOD;

    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long n, m, r, c;
        cin >> n >> m >> r >> c;

        long long freeCells =
            n * m - (n - r + 1) * (m - c + 1);

        cout << power(2, freeCells) << '\n';
    }

    return 0;
}