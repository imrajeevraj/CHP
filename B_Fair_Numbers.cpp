#include <bits/stdc++.h>
using namespace std;

bool isFair(unsigned long long x) {
    unsigned long long t = x;
    while (t > 0) {
        int d = t % 10;
        t /= 10;
        if (d != 0 && x % d != 0) return false;
    }
    return true;
}

int main() {

    int t;
    cin >> t;
    while (t--) {
        unsigned long long n;
        cin >> n;
        while (!isFair(n)) n++;
        cout << n << "\n";
    }
    return 0;
}