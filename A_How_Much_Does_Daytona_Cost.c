# include <stdio.h>
# include <stdbool.h>

int main(){
    int t;
    scanf("%d", &t);

    while (t-- > 0){
        int n,m;
        bool find = false;
        scanf("%d", &n);
        scanf("%d", &m);
        for(int i = 0; i < n; i++){
            int x;
            scanf("%d", &x);
            if(x == m){
                find = true;
            }
        }
        if(find){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
    
}