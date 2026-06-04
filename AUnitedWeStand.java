import java.util.*;

public class AUnitedWeStand {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-- > 0){
            int n = sc.nextInt();
            int[] arr = new int[n];
            for(int i = 0; i < n; i++){
                arr[i] = sc.nextInt();
            }
            Arrays.sort(arr);
            ArrayList<Integer> a = new ArrayList<>();
            ArrayList<Integer> b = new ArrayList<>();
            int min = arr[0];
            for(int i : arr){
                if (min == i){
                    a.add(i);
                }else{
                    b.add(i);
                }
            }
            if (b.size() == 0){
                System.out.println(-1);
            }else{
                System.out.println(a.size() + " " + b.size());
                for(int i: a){
                    System.out.print(i+" ");
                }
                System.out.println();
                for(int i: b){
                    System.out.print(i+" ");
                }
                System.out.println();
            }

        }
        sc.close();
    }
}