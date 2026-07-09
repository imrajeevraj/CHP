#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int count = 0;
    for (int i = 0; i < n; ++i) {
        int p, q;
        cin >> p >> q;
        if (q - p >= 2) {
            ++count;
        }
    }

    cout << count << '\n';
    return 0;
}