import java.util.*;

public class ENegativesAndPositives {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int t = sc.nextInt();
        
        while (t-- > 0) {
            int n = sc.nextInt();
            
            long sum = 0;
            int negCount = 0;
            long minAbs = Long.MAX_VALUE;
            
            for (int i = 0; i < n; i++) {
                long val = sc.nextLong();
                if (val < 0) {
                    negCount++;
                }
                long absVal = Math.abs(val);
                sum += absVal;
                minAbs = Math.min(minAbs, absVal);
            }
            
            if (negCount % 2 != 0) {
                sum -= 2 * minAbs;
            }
            
            System.out.println(sum);
        }
        
        sc.close();
    }
}