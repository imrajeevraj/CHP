import java.util.*;

public class AWeNeedTheZero {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0){
            int n = sc.nextInt();
            int x = 0;
            for(int i = 0; i < n; i++){
                int a =  sc.nextInt();
                x ^= a;
            }

            if (n % 2 == 1){
                System.out.println(x);
            }else{
                if (x == 0){
                    System.out.println(0);   
                }else{
                    System.out.println(-1);  
                }
            }
            
        }
        sc.close();;
    }
}
