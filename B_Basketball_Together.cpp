#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long D;
    cin >> n >> D;

    vector<long long> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());

    int l = 0;
    int r = n - 1;
    int ans = 0;

    while (l <= r) {
        long long need = D / a[r] + 1;

        if (r - l + 1 >= need) {
            ans++;
            l += (int)(need - 1);
            r--;
        } else {
            break;
        }
    }

    cout << ans << '\n';

    return 0;
}