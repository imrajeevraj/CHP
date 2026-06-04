#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        long long a, b;
        int n;

        scanf("%lld %lld %d", &a, &b, &n);

        long long ans = b;

        for (int i = 0; i < n; i++) {
            long long x;
            scanf("%lld", &x);

            if (x > a - 1)
                ans += (a - 1);
            else
                ans += x;
        }

        printf("%lld\n", ans);
    }

    return 0;
}