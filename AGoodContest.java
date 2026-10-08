import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class AGoodContest {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());
        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            String[] parts = br.readLine().trim().split("\\s+");
            int a = Integer.parseInt(parts[0]);
            int b = Integer.parseInt(parts[1]);
            int c = Integer.parseInt(parts[2]);
            int min = Math.min(a, Math.min(b, c));
            sb.append(n - min).append(System.lineSeparator());
        }

        System.out.print(sb.toString());
    }
}
