#include <bits/stdc++.h>
using namespace std;

int check(string n, char a, char b) {
    int del = 0;

    int pos_b = -1;

    // find second digit
    for (int i = n.size() - 1; i >= 0; i--) {
        if (n[i] == b) {
            pos_b = i;
            break;
        }
        del++;
    }

    if (pos_b == -1) return 100;


    for (int i = pos_b - 1; i >= 0; i--) {
        if (n[i] == a) {
            return del;
        }
        del++;
    }

    return 100;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        string n;
        cin >> n;

        int ans = 100;

        ans = min(ans, check(n, '0', '0'));
        ans = min(ans, check(n, '2', '5'));
        ans = min(ans, check(n, '5', '0'));
        ans = min(ans, check(n, '7', '5'));

        cout << ans << "\n";
    }
}