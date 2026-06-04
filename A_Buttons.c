# include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);

    while (t-- > 0){
        int a,b,c;
        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &c);

        if (c % 2 != 0){
            a++;
        }

        if (a > b){
            printf("First\n");
        }else{
            printf("Second\n");
        }

    }
    return 0;
}