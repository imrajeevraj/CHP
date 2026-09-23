import java.util.*;
import java.io.*;

public class BGcdPartition {
    public static void main(String[] args) throws IOException {
        FastScanner scanner = new FastScanner();
        StringBuilder sb = new StringBuilder();

        int t = scanner.nextInt();
        while (t-- > 0) {
            int n = scanner.nextInt();
            long[] a = new long[n];
            long totalSum = 0;
            for (int i = 0; i < n; i++) {
                a[i] = scanner.nextLong();
                totalSum += a[i];
            }

            long maxGcd = 1;
            long prefixSum = 0;
            
            for (int i = 0; i < n - 1; i++) {
                prefixSum += a[i];
                long currentGcd = gcd(prefixSum, totalSum - prefixSum);
                if (currentGcd > maxGcd) {
                    maxGcd = currentGcd;
                }
            }

            sb.append(maxGcd).append("\n");
        }

        System.out.print(sb);
    }

    private static long gcd(long a, long b) {
        while (b != 0) {
            long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    
    static class FastScanner {
        private final BufferedReader br;
        private StringTokenizer st;

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        public String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    String line = br.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return st.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }
}
