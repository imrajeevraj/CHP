import java.io.BufferedInputStream;
import java.io.IOException;

public class BMonocarpAndProjects {
    private static final class FastScanner {
        private final BufferedInputStream input = new BufferedInputStream(System.in);
        private final byte[] buffer = new byte[1 << 16];
        private int position;
        private int length;

        private int read() throws IOException {
            if (position == length) {
                length = input.read(buffer);
                position = 0;
                if (length == -1) {
                    return -1;
                }
            }
            return buffer[position++];
        }

        long nextLong() throws IOException {
            int character;
            do {
                character = read();
            } while (character <= ' ' && character != -1);

            long value = 0;
            while (character > ' ') {
                value = value * 10 + character - '0';
                character = read();
            }
            return value;
        }
    }

    public static void main(String[] args) throws IOException {
        FastScanner scanner = new FastScanner();
        int testCases = (int) scanner.nextLong();
        StringBuilder answer = new StringBuilder();

        while (testCases-- > 0) {
            long x = scanner.nextLong();
            long y = scanner.nextLong();
            long k = scanner.nextLong();
            long difference = y - x;

            long changingMonths = Math.min(k, Math.max(0, difference - x + 1));
            long total = 0;

            for (long i = 0; i < changingMonths; i++) {
                total += difference % (x + i);
            }

            total += (k - changingMonths) * difference;
            answer.append(total).append('\n');
        }

        System.out.print(answer);
    }
}