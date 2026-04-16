public class AreaTest {
    public static void main(String[] args) {
        Circle circle = new Circle();
        circle.radius = 50;
        Rectangle rectangle = new Rectangle();
        rectangle.width = 20;
        rectangle.height = 30;

        double circleArea = circle.area();
        double rectangleArea = rectangle.area();
        System.out.println("学号 202483290476 姓名 张正珂 ");
        System.out.println("圆的面积为 " + circleArea);
        System.out.println("矩形的面积为 " + rectangleArea);
    }
}