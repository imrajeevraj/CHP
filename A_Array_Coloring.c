# include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);

    while (t-- > 0){
        int n, sum = 0;
        scanf("%d", &n);
        for(int i = 0; i < n ; i++){
            int m;
            scanf("%d", &m);
            sum+=m;
        }
        printf(sum % 2 == 0 ? "YES\n" : "NO\n");
    }
    return 0;
    
}