import java.util.*;

public class AUnitArray {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0){
            int n = sc.nextInt();
            int neg = 0;
            int pos = 0;
            for(int i = 0; i < n; i++){
                if(sc.nextInt() == -1){
                    neg++;
                }else{
                    pos++;
                }
            }
            int ans = 0;
            while (neg > pos){
                neg--;
                pos++;
                ans++;                
            }
            if (neg % 2 == 1) {
                ans++;
            }
            System.out.println(ans);
            
        }
        sc.close();
    }
}