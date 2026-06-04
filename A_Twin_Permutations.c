# include<stdio.h>



int main() {
    int t;
    scanf("%d", &t);

    while (t-- > 0) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            printf("%d ", n + 1 - x);
        }
        printf("\n");
    }
    return 0;
}