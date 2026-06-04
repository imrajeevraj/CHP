#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {

        int n;
        scanf("%d", &n);

        int b[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }

        int a[2 * n];
        int k = 0;

        a[k++] = b[0];

        for (int i = 1; i < n; i++) {

            if (b[i - 1] <= b[i]) {
                a[k++] = b[i];
            } else {
                a[k++] = 1;
                a[k++] = b[i];
            }
        }

        printf("%d\n", k);

        for (int i = 0; i < k; i++) {
            printf("%d ", a[i]);
        }

        printf("\n");
    }

    return 0;
}