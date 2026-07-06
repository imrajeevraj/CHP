#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    string s;
    cin >> s;

    // Simulate t seconds
    while (t--) {
        // Go left to right, swap "BG" -> "GB"
        for (int i = 0; i + 1 < n; ) {
            if (s[i] == 'B' && s[i + 1] == 'G') {
                swap(s[i], s[i + 1]);
                i += 2; // skip next since this boy just moved there
            } else {
                i++;
            }
        }
    }

    cout << s << '\n';
    return 0;
}