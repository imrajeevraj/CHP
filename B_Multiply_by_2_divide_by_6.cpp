#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;

        int count_two = 0, count_three = 0;

        while (n % 2 == 0) {
            count_two++;
            n /= 2;
        }

        while (n % 3 == 0) {
            count_three++;
            n /= 3;
        }

        if (n != 1 || count_two > count_three) {
            cout << -1 << "\n";
        } else {
            cout << (2 * count_three - count_two) << "\n";
        }
    }

    return 0;
}