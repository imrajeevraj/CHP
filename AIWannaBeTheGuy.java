import java.util.Scanner;
import java.util.HashSet;
import java.util.Set;

public class AIWannaBeTheGuy {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        
        int n = scanner.nextInt();
        
        
        Set<Integer> passedLevels = new HashSet<>();
        
        
        int p = scanner.nextInt();
        for (int i = 0; i < p; i++) {
            passedLevels.add(scanner.nextInt());
        }
        
    
        int q = scanner.nextInt();
        for (int i = 0; i < q; i++) {
            passedLevels.add(scanner.nextInt());
        }
        
        
        if (passedLevels.size() == n) {
            System.out.println("I become the guy.");
        } else {
            System.out.println("Oh, my keyboard!");
        }
        
        scanner.close();
    }
}