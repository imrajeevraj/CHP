#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, a, b;
        scanf("%d %d %d", &n, &a, &b);

        if ((a + b <= n - 2) || (a == n && b == n))
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}