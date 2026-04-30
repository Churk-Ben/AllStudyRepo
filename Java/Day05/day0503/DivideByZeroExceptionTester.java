package day0503;

public class DivideByZeroExceptionTester {
    private static int quoient(int numerator, int denominator) throws DivideByZeroException {
        if (denominator == 0) {
            throw new DivideByZeroException();
        }
        return numerator / denominator;
    }

    public static void main(String[] args) {
        int a = 0, b = 0, res = 0;
        try {
            System.out.println("输入第一个数：");
            a = Integer.valueOf(Keyboard.getString().trim()).intValue();
            System.out.println("输入第二个数：");
            b = Integer.valueOf(Keyboard.getString().trim()).intValue();
            res = quoient(a, b);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input");
            System.exit(-1);
        } catch (DivideByZeroException e) {
            System.out.println(e.toString());
            System.exit(-1);
        }
        System.out.println("a / b = " + res);
    }
}
