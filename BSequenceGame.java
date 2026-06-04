import java.io.*;
import java.util.*;

public class BSequenceGame {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            long[] b = new long[n];
            for (int i = 0; i < n; i++) b[i] = fs.nextLong();

            List<Long> a = new ArrayList<>();
            a.add(b[0]);

            for (int i = 1; i < n; i++) {
                if (b[i] >= b[i - 1]) {
                    a.add(b[i]);
                } else {
                    a.add(b[i]);
                    a.add(b[i]);
                }
            }

            out.append(a.size()).append('\n');
            for (int i = 0; i < a.size(); i++) {
                if (i > 0) out.append(' ');
                out.append(a.get(i));
            }
            out.append('\n');
        }

        System.out.print(out.toString());
    }

    private static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream is) { in = is; }

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;
            do { c = read(); } while (c <= ' ' && c != -1);
            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }
            return sb.toString();
        }

        int nextInt() throws IOException { return Integer.parseInt(next()); }
        long nextLong() throws IOException { return Long.parseLong(next()); }
    }
}