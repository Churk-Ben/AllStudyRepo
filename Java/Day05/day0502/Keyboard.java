package day0502;

import java.io.*;

public class Keyboard {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static int getInteger() {
        try {
            return (Integer.valueOf(br.readLine().trim()).intValue());
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    public static String getString() {
        try {
            return br.readLine();
        } catch (IOException e) {
            return "0";
        }
    }
}
