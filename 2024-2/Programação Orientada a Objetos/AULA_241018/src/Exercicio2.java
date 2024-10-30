import java.io.*;

public class Exercicio2 {

    public static void file1() {
        try {
            File file = new File("resources/arquivo1.txt");
            FileWriter fw = new FileWriter(file, true);
            fw.write(generateTable(5));
            fw.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void file2() {
        try {
            File file1 = new File("resources/arquivo1.txt");
            File file2 = new File("resources/arquivo2.txt");

            FileReader fr = new FileReader(file1);
            FileWriter fw = new FileWriter(file2, true);
            BufferedReader br = new BufferedReader(fr);
            StringBuilder lines = new StringBuilder();

            br.lines().forEach(line -> lines.append(line).append("\n"));
            fw.write(lines.toString());
            fw.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static String generateTable(int n) {
        StringBuilder sb = new StringBuilder();

        for (int i = 1; i <= n; i++) {
            sb.append(i).append(" X ").append(n).append(": ").append((i*n)).append("\n");
        }

        return sb.toString();
    }
}
