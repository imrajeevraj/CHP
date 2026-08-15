import java.util.*;

public class ECardboardForPictures {

    static boolean check(long w, long[] a, long c) {
        long sum = 0;

        for (long x : a) {
            long side = x + 2 * w;
            long area = side * side;

            sum += area;

            if (sum > c) {
                return false;
            }
        }

        return sum == c;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            long c = sc.nextLong();

            long[] a = new long[n];

            for (int i = 0; i < n; i++) {
                a[i] = sc.nextLong();
            }

            long low = 1;
            long high = 1_000_000_000L;
            long ans = 0;

            while (low <= high) {
                long mid = low + (high - low) / 2;

                if (check(mid, a, c)) {
                    ans = mid;
                    break;
                }

                long sum = 0;

                for (long x : a) {
                    long side = x + 2 * mid;
                    sum += side * side;

                    if (sum > c) {
                        break;
                    }
                }

                if (sum < c) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            System.out.println(ans);
        }

        sc.close();
    }
}