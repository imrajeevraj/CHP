import java.io.*;
import java.util.*;

public class B2DTraveling {

    static long distance(long x1, long y1, long x2, long y2) {
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int t = Integer.parseInt(br.readLine());

        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            long[] x = new long[n + 1];
            long[] y = new long[n + 1];

            for (int i = 1; i <= n; i++) {
                st = new StringTokenizer(br.readLine());
                x[i] = Long.parseLong(st.nextToken());
                y[i] = Long.parseLong(st.nextToken());
            }

            long direct = distance(x[a], y[a], x[b], y[b]);

            long minA = Long.MAX_VALUE;
            long minB = Long.MAX_VALUE;

            for (int i = 1; i <= k; i++) {
                minA = Math.min(minA, distance(x[a], y[a], x[i], y[i]));
                minB = Math.min(minB, distance(x[b], y[b], x[i], y[i]));
            }

            long answer = direct;

            if (k > 0) {
                answer = Math.min(answer, minA + minB);
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}