package day0505;

import java.io.*;

public class BufferedReaderTester {
    public static void main(String[] args) throws IOException {
        String filename = "./Hello.txt";
        String line;

        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            line = br.readLine();
            while (line != null) {
                System.out.println(line);
                line = br.readLine();
            }
            br.close();
        } catch (IOException e) {
            System.out.println("张正珂没找到文件" + filename + "在哪儿!");
        }
    }
}
