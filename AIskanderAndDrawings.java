import java.util.Scanner;

public class AIskanderAndDrawings {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (!scanner.hasNextInt()) return;
        
        int t = scanner.nextInt();
        while (t-- > 0) {
            int n = scanner.nextInt();
            String s = scanner.next();
            
            int maxLen = 0;
            int currLen = 0;
            
            for (int i = 0; i < n; i++) {
                if (s.charAt(i) == '#') {
                    currLen++;
                    if (currLen > maxLen) {
                        maxLen = currLen;
                    }
                } else {
                    currLen = 0;
                }
            }
            
            System.out.println((maxLen + 1) / 2);
        }
        scanner.close();
    }
}