#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int current = 0, capacity = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;

        current -= a;
        current += b;
        capacity = max(capacity, current);
    }

    cout << capacity << '\n';
    return 0;
}