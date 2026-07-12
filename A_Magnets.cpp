#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string prev, cur;
    cin >> prev;           // read first magnet
    int groups = 1;        // at least one group

    for (int i = 1; i < n; ++i) {
        cin >> cur;
        if (cur != prev)   // orientation changed -> new group
            ++groups;
        prev = cur;
    }

    cout << groups << '\n';
    return 0;
}