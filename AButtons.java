import java.util.*;

public class AButtons{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0){
            int a,b,c;
            a = sc.nextInt();
            b = sc.nextInt();
            c = sc.nextInt();
            if (c % 2 != 0){
                a++;
            }
            if (a > b){
                System.out.println("First");
            }else{
                System.out.println("Second");
            }

            
        }
        sc.close();
    }
}