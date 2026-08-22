import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class B_JoJo_s_Incredible_Adventures {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        if (line == null) return;
        int t = Integer.parseInt(line.trim());
        
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            String s = reader.readLine().trim();
            int n = s.length();
            
            boolean allOnes = true;
            for (int i = 0; i < n; i++) {
                if (s.charAt(i) == '0') {
                    allOnes = false;
                    break;
                }
            }
            
            if (allOnes) {
                long ans = (long) n * n;
                sb.append(ans).append("\n");
            } else {
                String doubleS = s + s;
                long maxL = 0;
                long currentL = 0;
                for (int i = 0; i < doubleS.length(); i++) {
                    if (doubleS.charAt(i) == '1') {
                        currentL++;
                        if (currentL > maxL) {
                            maxL = currentL;
                        }
                    } else {
                        currentL = 0;
                    }
                }
                
                long side1 = (maxL + 1) / 2;
                long side2 = (maxL + 2) / 2;
                long ans = side1 * side2;
                sb.append(ans).append("\n");
            }
        }
        System.out.print(sb);
    }
}
