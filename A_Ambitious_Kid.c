# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

int main(){
    int t, x;
    scanf("%d", &t);
    int ans = INT_MAX;
    for(int i = 0; i < t; i++){
        scanf("%d", &x);
        if (abs(x)< ans){
            ans = abs(x);
        }
    }
    printf("%d\n", ans);


    return 0;
}