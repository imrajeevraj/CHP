# include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);

    while (t-- > 0){
        int a,b;
        scanf("%d", &a);
        scanf("%d", &b);
        if (a % b != 0){
            printf("1\n");
            printf("%d\n", a);
        }else{
        printf("2\n");
        printf("%d %d\n", 1,(a-1));
        }
    
    }
    return 0;
}