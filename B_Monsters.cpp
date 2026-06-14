#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first)
        return a.first > b.first;   
    return a.second < b.second;     
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<pair<int, int> > v;

        for (int i = 1; i <= n; i++) {
            long long a;
            cin >> a;

            int rem = a % k;
            if (rem == 0)
                rem = k;

            v.push_back(make_pair(rem, i));
        }

        sort(v.begin(), v.end(), cmp);

        for (int i = 0; i < n; i++) {
            cout << v[i].second;
            if (i + 1 < n) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}