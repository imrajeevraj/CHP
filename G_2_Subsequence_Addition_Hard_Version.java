import java.io.*;
import java.util.*;

public class G_2_Subsequence_Addition_Hard_Version {

    public static void main(String[] args) {
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            long[] a = new long[n];
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextLong();
            }

            // Shuffle array to prevent worst-case O(n^2) quicksort behavior
            shuffle(a);
            Arrays.sort(a);

            if (a[0] != 1) {
                out.println("NO");
                continue;
            }

            long sum = 1;
            boolean ok = true;
            for (int i = 1; i < n; i++) {
                if (a[i] > sum) {
                    ok = false;
                    break;
                }
                // Safe addition with saturation at Long.MAX_VALUE to prevent overflow
                if (sum <= Long.MAX_VALUE - a[i]) {
                    sum += a[i];
                } else {
                    sum = Long.MAX_VALUE;
                }
            }

            if (ok) {
                out.println("YES");
            } else {
                out.println("NO");
            }
        }
        out.flush();
    }

    private static void shuffle(long[] a) {
        Random rand = new Random();
        for (int i = 0; i < a.length; i++) {
            int j = rand.nextInt(i + 1);
            long temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }
}
