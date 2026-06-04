import java.util.*;

public class AHowMuchDoesDaytonaCost {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0){
            int n = sc.nextInt();
            int m = sc.nextInt();
            boolean found = false;
            for(int i = 0; i < n; i++){
                int x = sc.nextInt();
                if(m == x){
                    found = true;
                }
            }
            System.out.println(found ? "YES": "NO");
        }

        sc.close();
    }

}