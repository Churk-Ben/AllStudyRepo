#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void verify_goldbach(int limit) {
    for (int even = 4; even <= limit; even += 2) {
        bool found = false;
        for (int i = 2; i <= even / 2; i++) {
            if (is_prime(i) && is_prime(even - i)) {
                found = true;
                break;
            }
        }
        if (!found) {
            printf("哥德巴赫猜想在 %d 不成立.\n", even);
            return;
        }
    }
    printf("哥德巴赫猜想在 %d 以内成立.\n", limit);
}

int main() {
    int limit;
    printf("请输入要验证的最大偶数（大于等于 4）：");
    scanf("%d", &limit);
    verify_goldbach(limit);
    return 0;
}
