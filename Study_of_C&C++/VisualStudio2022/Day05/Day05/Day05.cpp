//#include <stdio.h>
//#include <math.h>
//
//int main()
//{
//    double a, b, c, s, area;
//    while (scanf_s("%lf %lf %lf", &a, &b, &c) != EOF)
//    {
//        if ((a + b > c) && (a + c > b) && (b + c > a))
//        {
//            s = (a + b + c) / 2.0;
//
//            area = sqrt(s * (s - a) * (s - b) * (s - c));
//
//            printf("%.2f\n", area);
//        }
//        else
//        {
//            printf("-1\n");
//        }
//    }
//
//    return 0;
//}

//#include <stdio.h>
//int main()
//{
//    printf(" O \n");
//    printf("<H>\n");
//    printf("I I\n");
//    printf("   \n");
//    printf(" O \n");
//    printf("<H>\n");
//    printf("I I\n");
//    return 0;
//}

#include <stdio.h>

int main()
{
    double x, y;
    char c1, c2, c3;
    int a1, a2, a3;

    scanf_s("%d %d %d", &a1, &a2, &a3);    // 取址符 &
    printf("a1 = %d, a2 = %d, a3 = %d\n", a1, a2, a3);
    getchar();

    scanf_s("%lf,%lf", &x, &y);    // 定义为double
    printf("x = %f, y = %lf\n", x, y);
    getchar();

    scanf_s("%c", &c1);    // 多了就不行，不懂了
    printf("c1 = %c\n", c1);
    getchar();

    return 0;
}