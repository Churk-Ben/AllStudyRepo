#include <stdio.h>

void move(int from, int to) {
    printf("%d -> %d\n", from, to);
}

void hanoi(int n, int a, int b, int c) {
    int totalMoves = (1 << n) - 1;
    int i;

    for (i = 1; i <= totalMoves; i++) {
        if (i % 3 == 1) {
            move(a, c);
        } else if (i % 3 == 2) {
            move(a, b);
        } else if (i % 3 == 0) {
            move(b, c);
        }

        if (n % 2 == 0) {
            if (i % 3 == 1) {
                move(b, c);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    hanoi(n, 1, 2, 3);
    return 0;
}
