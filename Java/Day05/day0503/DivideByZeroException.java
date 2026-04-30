package day0503;

public class DivideByZeroException extends ArithmeticException {
    public DivideByZeroException() {
        super("Division by zero");
    }
}
