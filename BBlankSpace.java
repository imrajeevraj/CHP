import java.util.*;

public class BBlankSpace {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0){

            int n = sc.nextInt();

            int count = 0;
            int temp = 0;

            for(int i = 0; i < n; i++){

                int x = sc.nextInt();

                if (x == 0){
                    temp++;
                } else {

                    count = Math.max(count, temp);

                    temp = 0;
                }
            }
            count = Math.max(count, temp);

            System.out.println(count);
        }

        sc.close();
    }
}