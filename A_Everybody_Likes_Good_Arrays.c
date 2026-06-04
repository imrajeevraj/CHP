#include <stdio.h>

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);

        int a[200005]; 
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        int ops = 0;
        for (int i = 0; i + 1 < n; i++){
            int p1 = a[i] % 2;       
            int p2 = a[i + 1] % 2; 
            if (p1 == p2){
                ops++;
            }
        }

        printf("%d\n", ops);
    }
    return 0;
}