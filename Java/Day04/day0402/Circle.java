public class Circle {
    static double PI = 3.1415926;
    int radius;

    public double circumference() {
        return 2 * PI * radius;
    }

    public double area() {
        return PI * radius * radius;
    }
}