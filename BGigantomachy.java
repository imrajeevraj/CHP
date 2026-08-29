import java.util.*;

public class BGigantomachy {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();

            long[] a = new long[n];
            long[] b = new long[m];

            for (int i = 0; i < n; i++) {
                a[i] = sc.nextLong();
            }

            for (int i = 0; i < m; i++) {
                b[i] = sc.nextLong();
            }

            long bea = a[0] + n - 1;
            long ver = b[0] + m - 1;

            if (bea >= ver) {
                System.out.println(1);
            } else {
                System.out.println(2);
            }
        }

        sc.close();
    }
}