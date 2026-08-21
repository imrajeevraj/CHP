import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class B_Sort_the_Subarray {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;
        
        String line = br.readLine();
        if (line == null) return;
        st = new StringTokenizer(line);
        int t = Integer.parseInt(st.nextToken());
        
        StringBuilder sb = new StringBuilder();
        
        while (t-- > 0) {
            line = br.readLine();
            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }
            if (line == null) break;
            st = new StringTokenizer(line);
            int n = Integer.parseInt(st.nextToken());
            
            int[] a = new int[n];
            line = br.readLine();
            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }
            st = new StringTokenizer(line);
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
            }
            
            int[] aDiff = new int[n];
            line = br.readLine();
            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }
            st = new StringTokenizer(line);
            for (int i = 0; i < n; i++) {
                aDiff[i] = Integer.parseInt(st.nextToken());
            }
            
            int firstDiff = -1, lastDiff = -1;
            for (int i = 0; i < n; i++) {
                if (a[i] != aDiff[i]) {
                    if (firstDiff == -1) firstDiff = i;
                    lastDiff = i;
                }
            }
            
            int ansL, ansR;
            if (firstDiff != -1) {
                int left = firstDiff;
                int right = lastDiff;
                
                while (left > 0 && aDiff[left - 1] <= aDiff[left]) {
                    left--;
                }
                while (right < n - 1 && aDiff[right + 1] >= aDiff[right]) {
                    right++;
                }
                ansL = left + 1;
                ansR = right + 1;
            } else {
                int bestL = 0, bestR = 0, curL = 0;
                for (int i = 0; i < n; i++) {
                    if (i > 0 && aDiff[i - 1] > aDiff[i]) {
                        curL = i;
                    }
                    if (i - curL > bestR - bestL) {
                        bestL = curL;
                        bestR = i;
                    }
                }
                ansL = bestL + 1;
                ansR = bestR + 1;
            }
            
            sb.append(ansL).append(" ").append(ansR).append("\n");
        }
        
        System.out.print(sb);
    }
}
