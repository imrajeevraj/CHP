#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n, r, b;
        cin >> n >> r >> b;

        int parts = b + 1;
        int big = r % parts;
        int smallSize = r / parts;

        for (int i = 0; i < parts; i++) {
            int cnt = smallSize + (i < big ? 1 : 0);
            while (cnt--) cout << 'R';
            if (i < b) cout << 'B';
        }
        cout << '\n';
    }

    return 0;
}