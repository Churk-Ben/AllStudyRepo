package day0504;

import java.io.*;

public class FileWriterTester1 {
    public static void main(String[] args) throws IOException {
        String filename = "./Hello.txt";
        FileWriter fw = new FileWriter(filename);
        fw.write("Hello World!\n");
        fw.write("--From 202483290476 张正珂\n");
        fw.close();
    }
}
