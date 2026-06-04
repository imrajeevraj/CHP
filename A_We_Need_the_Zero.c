#include <stdio.h>

int main(void) {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        int n;
        scanf("%d", &n);

        int x = 0;
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            x ^= a;            
        }

        if (n % 2 == 1) {
        
            printf("%d\n", x);
        } else {
        
            if (x == 0) printf("0\n");
            else printf("-1\n");
        }
    }

    return 0;
}