#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    int t;
    cin >> t;

    while (t--) {

        int n;
        ll q;
        cin >> n >> q;

        vector<ll> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<ll> sortedArray = a;
        sort(sortedArray.begin(), sortedArray.end());

        vector<ll> uniqueValues = sortedArray;
        uniqueValues.erase(unique(uniqueValues.begin(), uniqueValues.end()), uniqueValues.end());

        int m = uniqueValues.size();

        unordered_map<ll, int> index;
        index.reserve(m * 2);

        for (int i = 0; i < m; i++) {
            index[uniqueValues[i]] = i;
        }

        vector<ull> hash1(m), hash2(m);

        for (int i = 0; i < m; i++) {
            hash1[i] = rng();
            hash2[i] = rng();
        }

        vector<ull> prefixA1(n + 1, 0);
        vector<ull> prefixA2(n + 1, 0);
        vector<ull> prefixS1(n + 1, 0);
        vector<ull> prefixS2(n + 1, 0);

        for (int i = 0; i < n; i++) {

            int ia = index[a[i]];
            int is = index[sortedArray[i]];

            prefixA1[i + 1] = prefixA1[i] + hash1[ia];
            prefixA2[i + 1] = prefixA2[i] + hash2[ia];

            prefixS1[i + 1] = prefixS1[i] + hash1[is];
            prefixS2[i + 1] = prefixS2[i] + hash2[is];
        }

        int answerPower = 0;

        while (true) {

            ll blockSize = 1LL << answerPower;
            bool possible = true;

            for (ll start = 0; start < n; start += blockSize) {

                ll end = min((ll)n, start + blockSize);

                if (prefixA1[end] - prefixA1[start] != prefixS1[end] - prefixS1[start] ||
                    prefixA2[end] - prefixA2[start] != prefixS2[end] - prefixS2[start]) {
                    possible = false;
                    break;
                }
            }

            if (possible || blockSize >= n) {
                break;
            }

            answerPower++;
        }

        if (answerPower == 0)
            cout << 0 << '\n';
        else
            cout << (1LL << (answerPower - 1)) << '\n';
    }

    return 0;
}