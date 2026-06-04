# include<stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    while (t-- > 0)
    {
        int n, first;
        scanf("%d", &n);
        scanf("%d", &first);
        //Read remaining degit
        for(int i = 1; i < n; i++){
            int j;
            scanf("%d", &j);
        }
        if(first == 1){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    
}
