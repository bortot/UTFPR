import java.io.File;

public class Main {

    public static void main(String[] args) {
        File file = new File("resources/arquivo1.txt");
        file.createNewFile();
    }
}