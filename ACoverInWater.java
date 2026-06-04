import java.util.*;

public class ACoverInWater {
    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t--> 0){
            int n = sc.nextInt();
            String s = sc.next();
            if (s.contains("...")){
                System.out.println(2);
            }
            else{
                int count = 0;
                for (int i = 0; i < n ; i++){
                    if (s.charAt(i) == '.')
                        count++;
                }
                System.out.println(count);
            }

        }
        sc.close();
    }
}
