#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string a, b;
        cin >> a >> b;

        int best = 0;

        for (int i = 0; i < (int)a.size(); i++) {
            for (int len = 1; i + len <= (int)a.size(); len++) {
                string cur = a.substr(i, len);
                if (b.find(cur) != string::npos)
                    best = max(best, len);
            }
        }

        cout << a.size() + b.size() - 2 * best << '\n';
    }

    return 0;
}