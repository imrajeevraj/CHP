# include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);

    while (t--){
        int n;
        scanf("%d", &n);
        int num[n];
        for (int i = 0; i < n; i++){
            scanf("%d", &num[i]);
            if (num[i] == 1){
                num[i]+=1;
            }
        }
        for (int i = 0; i < n - 1; i++){
            if(num[i+1] % num[i] == 0){
                num[i+1] += 1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            printf("%d ", num[i]);
        }
        printf("\n");
                
    }
    return 0;
    
}