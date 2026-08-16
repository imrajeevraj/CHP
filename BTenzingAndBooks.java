import java.io.*;
import java.util.*;

public class BTenzingAndBooks {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());

        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int x = Integer.parseInt(st.nextToken());

            int current = 0;

            for (int stack = 0; stack < 3; stack++) {
                st = new StringTokenizer(br.readLine());
                boolean stop = false;

                for (int i = 0; i < n; i++) {
                    int v = Integer.parseInt(st.nextToken());

                    if (!stop) {
                        int next = current | v;

                        if ((next & x) == next) {
                            current = next;
                        } else {
                            stop = true;
                        }
                    }
                }
            }

            System.out.println(current == x ? "Yes" : "No");
        }
    }
}
