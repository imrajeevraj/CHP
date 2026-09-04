import java.util.Scanner;

public class AWhoWatchesTheWatchpig {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        if (!sc.hasNextInt()) {
            sc.close();
            return;
        }

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            String s = sc.next();

            if (2 * k > n) {
                System.out.println(-1);
                continue;
            }

            int flips = 0;

       
            for (int i = 0; i < k; i++) {
                if (s.charAt(i) != 'R') {
                    flips++;
                }
            }

          
            for (int i = n - k; i < n; i++) {
                if (s.charAt(i) != 'L') {
                    flips++;
                }
            }

            System.out.println(flips);
        }

        sc.close();
    }
}