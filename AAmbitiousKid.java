import java.util.*;

public class AAmbitiousKid {
    public static void main(String[] args){
        Scanner sc =  new Scanner(System.in);
        int t = sc.nextInt();
        int ans = Integer.MAX_VALUE;
        for(int i = 0; i < t; i++ ){
            int x = sc.nextInt();
            ans = Math.min(ans, Math.abs(x));
        }
        System.out.println(ans);
        sc.close();
    }
}

