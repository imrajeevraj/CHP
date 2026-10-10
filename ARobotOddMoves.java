public class ARobotOddMoves {
    public static void main(String[] args) throws Exception {
        java.io.BufferedReader reader = new java.io.BufferedReader(
                new java.io.InputStreamReader(System.in));
        int testCases = Integer.parseInt(reader.readLine().trim());
        StringBuilder answer = new StringBuilder();

        for (int i = 0; i < testCases; i++) {
            String[] coordinates = reader.readLine().trim().split("\\s+");
            int a = Integer.parseInt(coordinates[0]);
            int b = Integer.parseInt(coordinates[1]);

            int operations;
            if ((a & 1) == (b & 1) && b <= a) {
                operations = a;
            } else if ((a & 1) != (b & 1) && b <= a + 1) {
                operations = a + 1;
            } else {
                operations = -1;
            }

            answer.append(operations).append('\n');
        }

        System.out.print(answer);
    }
}
