import java.util.*;

public class ADoremySPaint3 {
 public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {

            int n = sc.nextInt();

            HashMap<Integer, Integer> map = new HashMap<>();

            for (int i = 0; i < n; i++) {
                int x = sc.nextInt();
                map.put(x, map.getOrDefault(x, 0) + 1);
            }

            if (map.size() > 2) {
                System.out.println("No");
            } 
            else if (map.size() == 1) {
                System.out.println("Yes");
            } 
            else {

                ArrayList<Integer> freq = new ArrayList<>(map.values());

                if (Math.abs(freq.get(0) - freq.get(1)) <= 1) {
                    System.out.println("Yes");
                } else {
                    System.out.println("No");
                }
            }
        }
        sc.close();
    }
}