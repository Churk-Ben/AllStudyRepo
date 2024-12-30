// 一元二次方程求解

#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double delta, p1, p2; // 用于保存中间计算结果

    while(scanf("%lf%lf%lf", &a, &b, &c) != EOF) {
        if(a == 0) {
            printf("a = 0, invalid input\n");
            continue;
        }

        delta = b*b - 4*a*c;
        p1 = -b/2/a;
        p2 = sqrt(fabs(delta))/2/a;

        if(delta == 0)
            printf("x1 = x2 = %.2g\n", p1);
        else if(delta > 0)
            printf("x1 = %.2g, x2 = %.2g\n", p1+p2, p1-p2);
        else {
            printf("x1 = %.2g + %.2gi, ", p1, p2);
            printf("x2 = %.2g - %.2gi\n", p1, p2);
        }
    }

    return 0;
}