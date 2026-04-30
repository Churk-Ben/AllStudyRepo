package day0501;

public class ExceptionTester1 {
    public static void main(String[] args) {
        System.out.println("输入第一个数：");
        int a = Keyboard.getInteger();
        System.out.println("输入第二个数：");
        int b = Keyboard.getInteger();
        System.out.print("a / b = ");
        int res = a / b;
        System.out.println(res);
    }
}
