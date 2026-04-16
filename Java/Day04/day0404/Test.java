package day0404;

class A {
    int x = 2;

    public void setx(int x) {
        this.x = x;
    }

    void printa() {
        System.out.println(x);
    }
}

class B extends A {
    int x = 100;

    void printb() {
        super.x += 10;
        System.out.println("super.x = " + super.x + ", x = " + x);
    }
}

public class Test {
    public static void main(String[] args) {
        System.out.println("学号 202483290476 姓名 张正珂 ");
        A a1 = new A();
        a1.setx(4);
        a1.printa();

        B b1 = new B();
        b1.printb();
        b1.printa();

        b1.setx(6);
        b1.printb();
        b1.printa();

        a1.printa();
    }
}