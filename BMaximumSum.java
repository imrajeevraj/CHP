import java.util.*;

public class BMaximumSum{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            int k = sc.nextInt();

            long[] a = new long[n];

            for (int i = 0; i < n; i++) {
                a[i] = sc.nextLong();
            }

            Arrays.sort(a);

            long[] prefix = new long[n + 1];

            for (int i = 0; i < n; i++) {
                prefix[i + 1] = prefix[i] + a[i];
            }

            long ans = 0;

            for (int i = 0; i <= k; i++) {
                int left = 2 * i;
                int right = n - (k - i);

                long sum = prefix[right] - prefix[left];

                ans = Math.max(ans, sum);
            }

            System.out.println(ans);
        }

        sc.close();
    }
}
