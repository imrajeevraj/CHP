import java.util.*;

public class AForbiddenInteger{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-- > 0){
            int n = sc.nextInt();
            int k = sc.nextInt();
            int x = sc.nextInt();
            if (x != 1){
                System.out.println("YES");
                System.out.println(n);
                for (int i = 0; i < n; i++){
                    System.out.print("1 ");
                }
                System.out.println();
            }else {
                if (k == 1) {
                    System.out.println("NO");
                }

                else {

                    // n is even
                    if (n % 2 == 0) {

                        System.out.println("YES");
                        System.out.println(n / 2);

                        for (int i = 0; i < n / 2; i++) {
                            System.out.print("2 ");
                        }

                        System.out.println();
                    }

                    // n is odd
                    else {

                        // 3 must be available
                        if (k >= 3) {

                            System.out.println("YES");

                            int count = 1 + (n - 3) / 2;
                            System.out.println(count);

                            System.out.print("3 ");

                            for (int i = 0; i < (n - 3) / 2; i++) {
                                System.out.print("2 ");
                            }

                            System.out.println();
                        }

                        else {
                            System.out.println("NO");
                        }
                    }
                }
            }
        }

        sc.close();
    }
}