#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {

    int t;
    scanf("%d", &t);

    while (t--) {

        int n;
        scanf("%d", &n);

        int arr[n];

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        qsort(arr, n, sizeof(int), compare);

        int min = arr[0];

        int a[n], b[n];
        int sizeA = 0, sizeB = 0;

        for (int i = 0; i < n; i++) {

            if (arr[i] == min) {
                a[sizeA++] = arr[i];
            } else {
                b[sizeB++] = arr[i];
            }
        }

        if (sizeB == 0) {

            printf("-1\n");

        } else {

            printf("%d %d\n", sizeA, sizeB);

            for (int i = 0; i < sizeA; i++) {
                printf("%d ", a[i]);
            }

            printf("\n");

            for (int i = 0; i < sizeB; i++) {
                printf("%d ", b[i]);
            }

            printf("\n");
        }
    }

    return 0;
}