#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            sum += x;
        }
        bool ok = (n % 2 == 0) && (((sum % 4) + 4) % 4 == 0);
        printf(ok ? "YES\n" : "NO\n");
    }
    return 0;
}