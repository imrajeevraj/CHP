import java.util.*;

public class ACreatingAbbreviations {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();

            Set<Character> available = new HashSet<>();

           
            for (int i = 0; i < n; i++) {
                String word = sc.next();
                available.add(Character.toUpperCase(word.charAt(0)));
            }

            String[] abbreviations = new String[m];

            for (int i = 0; i < m; i++) {
                abbreviations[i] = sc.next();
            }

            boolean[] created = new boolean[m];
            int count = 0;

           
            boolean changed = true;

            while (changed) {
                changed = false;

                for (int i = 0; i < m; i++) {
                    if (created[i]) continue;

                    String s = abbreviations[i];

                    boolean possible = true;

                    
                    for (char c : s.toCharArray()) {
                        if (!available.contains(c)) {
                            possible = false;
                            break;
                        }
                    }

                    if (possible) {
                        created[i] = true;
                        count++;
                        available.add(s.charAt(0));

                        changed = true;
                    }
                }
            }

            System.out.println(count == m ? "YES" : "NO");
        }

        sc.close();
    }
}