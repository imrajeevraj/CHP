#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n + 1), a(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];          
    }

    for (int i = 1; i <= n; ++i) {
        int receiver = p[i];
        a[receiver] = i;     
    }

    for (int j = 1; j <= n; ++j) {
        cout << a[j] << (j == n ? '\n' : ' ');
    }
    return 0;
}