# include<stdio.h>

int main(){
    int t;
    scanf("%d", &t);

    while (t--){
        int x, count = 0;
        scanf("%d", &x);
        if(x < 10){
            count = x;
        }else if (x < 100){
            count = 9 + (x / 10);
        }else if (x < 1000){
            count = 18 + (x / 100);
        }else if (x < 10000){
            count = 27 + (x / 1000);
        }else if(x < 100000){
            count = 36 + (x / 10000);
        }else{
            count = 45 + (x / 100000);
        }
        printf("%d\n", count);
    }
    return 0;
}