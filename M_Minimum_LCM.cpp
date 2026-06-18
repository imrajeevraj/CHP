#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;

        if (n % 2 == 0) {
            cout << n / 2 << " " << n / 2 << '\n';
            continue;
        }

        long long d = -1;
        for (long long i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                d = i;
                break;
            }
        }

        if (d == -1) {
            cout << 1 << " " << n - 1 << '\n';
        } else {
            long long a = n / d;
            cout << a << " " << n - a << '\n';
        }
    }

    return 0;
}