import java.io.*;
import java.util.*;

public class EBuildingAnAquarium {
     static boolean canBuild(long height, long[] a, long x) {
        long water = 0;

        for (long h : a) {
            if (h < height) {
                water += height - h;
            }

            if (water > x) {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int t = Integer.parseInt(br.readLine());

        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            int n = Integer.parseInt(st.nextToken());
            long x = Long.parseLong(st.nextToken());

            long[] a = new long[n];

            st = new StringTokenizer(br.readLine());

            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }

            long low = 1;
            long high = 2_000_000_000L;
            long answer = 0;

            while (low <= high) {
                long mid = low + (high - low) / 2;

                if (canBuild(mid, a, x)) {
                    answer = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            System.out.println(answer);
        }
    }
    
}
