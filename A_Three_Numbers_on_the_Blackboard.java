import java.util.*;

public class A_Three_Numbers_on_the_Blackboard {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        if (sc.hasNextInt()) {
            int t = sc.nextInt();
            while (t-- > 0) {
                int a = sc.nextInt();
                int b = sc.nextInt();
                int c = sc.nextInt();
                
                // O(1) sort without array allocations
                int min = Math.min(a, Math.min(b, c));
                int max = Math.max(a, Math.max(b, c));
                int mid = a + b + c - min - max;
                
                int range = Math.min(max - min, mid);
                
                System.out.println(range);
            }
        }
    }
}