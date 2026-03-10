#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n); // 输入数据行数

    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c); // 输入三条边的长度

        // 检查是否能构成三角形
        if (a + b <= c || a + c <= b || b + c <= a) {
            printf("Not Triangle\n");
        } 
        else if (a == b && b == c) {
            printf("Regular Triangle\n");
        } 
        else if (a == b || a == c || b == c) {
            printf("Isosceles Triangle\n");
        } 
        else {
            printf("Triangle\n");
        }
    }

    return 0;
}
