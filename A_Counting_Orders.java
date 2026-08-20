import java.io.*;
import java.util.*;

public class A_Counting_Orders {
    static final long MOD = 1000000007;

    public static void main(String[] args) {
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt();
            }
            int[] b = new int[n];
            for (int i = 0; i < n; i++) {
                b[i] = sc.nextInt();
            }

            randomShuffle(a);
            randomShuffle(b);
            Arrays.sort(a);
            Arrays.sort(b);

            long ans = 1;
            int j = n - 1;
            for (int i = n - 1; i >= 0; i--) {
                while (j >= 0 && a[j] > b[i]) {
                    j--;
                }
                int count = n - 1 - j;
                int choices = count - (n - 1 - i);
                if (choices <= 0) {
                    ans = 0;
                    break;
                }
                ans = (ans * choices) % MOD;
            }

            out.println(ans);
        }
        out.flush();
    }

    static void randomShuffle(int[] a) {
        Random rnd = new Random();
        for (int i = a.length - 1; i > 0; i--) {
            int j = rnd.nextInt(i + 1);
            int temp = a[i];
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
    }
}
