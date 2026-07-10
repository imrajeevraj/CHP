#include <bits/stdc++.h>
using namespace std;

int xorTo(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int a, b;
        cin >> a >> b;

        int x = xorTo(a - 1);

        if (x == b)
            cout << a << '\n';
        else if ((x ^ b) == a)
            cout << a + 2 << '\n';
        else
            cout << a + 1 << '\n';
    }

    return 0;
}