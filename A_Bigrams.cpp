#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int k;
        scanf("%d", &k);
        vector<long long> c(k);
        for (auto &x : c) scanf("%lld", &x);

        bool hasThree = false;
        int countGe2 = 0;
        for (auto x : c) {
            if (x >= 3) hasThree = true;
            if (x >= 2) countGe2++;
        }

        bool ans = hasThree || (countGe2 >= 2);
        printf(ans ? "YES\n" : "NO\n");
    }
}