import java.util.*;

public class AJellyfishAndUndertale {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t =  sc.nextInt();

        while (t-- > 0 ){
           long a = sc.nextInt();
           long b = sc.nextInt();
            int c = sc.nextInt();
            long ans = b;
            for(int i = 0; i < c; i++){
                long x = sc.nextInt();
                ans += Math.min(x, a-1);
            }
            System.out.println(ans); 
            
        }
    }
}