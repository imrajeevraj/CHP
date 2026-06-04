import java.util.*;

public class AGrasshopperOnALine{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0){
            int a = sc.nextInt();
            int b = sc.nextInt();
            if (a % b != 0){
                System.out.println(1);
                System.out.println(a);
            }else{
                System.out.println(2);
                System.out.println(1 + " " + (a-1));
            }

            
        }
        sc.close();
    }
}