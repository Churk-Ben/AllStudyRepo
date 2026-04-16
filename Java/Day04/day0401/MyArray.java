public class MyArray {
    public static void main(String[] args) {

        int[] myArray = new int[10];
        myArray[0] = 0;
        myArray[1] = 1;
        myArray[2] = 2;
        myArray[3] = 9;

        System.out.println("学号 202483290476 姓名 张正珂 ");

        System.out.println("Index\t\tValue");
        System.out.println("==================");
        for (int i = 0; i < myArray.length; i++) {
            System.out.println(i + "\t\t" + myArray[i]);
        }

        System.out.println("Values:");
        for (int value : myArray) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}