# include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t-- > 0){
        int n, neg = 0, pos = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            int p;
            scanf("%d", &p);
            if( p == -1){
                neg++;
            }else{
                    pos++;
                }
            }
            int ans = 0;
            while (neg > pos){
                neg--;
                pos++;
                ans++;                
            }
            if (neg % 2 == 1) {
                ans++;
            }
            printf("%d\n", ans);
            
    }
    return 0;
}