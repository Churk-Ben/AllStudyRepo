package day0502;

public class ExceptionTester3 {
    public static void main(String[] args) {
        int a = 0, b = 0, res = 0;

        try {
            System.out.println("输入第一个数：");
            a = Integer.valueOf(Keyboard.getString().trim()).intValue();
            System.out.println("输入第二个数：");
            b = Integer.valueOf(Keyboard.getString().trim()).intValue();
            res = a / b;
        } catch (NumberFormatException e) {
            System.out.println("Invalid input");
            System.exit(-1);
        } catch (ArithmeticException e) {
            System.out.println("Division by zero");
            System.exit(-1);
        }
        System.out.println("a / b = " + res);
    }
}
