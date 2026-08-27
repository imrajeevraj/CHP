import java.util.Scanner;

public class AHitTheLottery {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int count = 0;

        int[] notes = {100, 20, 10, 5, 1};

        for (int note : notes) {
            count += n / note;
            n %= note;
        }

        System.out.println(count);

        sc.close();
    }
}

