import java.util.*;

public class AArrivalOfTheGeneral {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] a = new int[n];

        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }

        int maxIndex = 0;
        int minIndex = 0;

        for (int i = 1; i < n; i++) {
            if (a[i] > a[maxIndex]) {
                maxIndex = i;
            }

            if (a[i] <= a[minIndex]) {
                minIndex = i;
            }
        }

        int swaps = maxIndex + (n - 1 - minIndex);

        if (maxIndex > minIndex) {
            swaps--;
        }

        System.out.println(swaps);
    }
}