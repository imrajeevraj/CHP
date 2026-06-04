#include <stdio.h>

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

        int a = arr[0], b = -1;
        int countA = 0, countB = 0;
        int valid = 1;

        for (int i = 0; i < n; i++) {

            if (arr[i] == a) {
                countA++;
            }
            else if (b == -1 || arr[i] == b) {

                if (b == -1)
                    b = arr[i];

                countB++;
            }
            else {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("No\n");
        }
        else {
            if (countB == 0 || (countA - countB <= 1 && countB - countA <= 1)) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
        }
    }

    return 0;
}