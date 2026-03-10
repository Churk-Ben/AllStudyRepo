#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define N1 397
#define N2 476
#define N3 21

int main() {
    int cnt;
    int random_major, random_no;

    srand(time(NULL));      // 以当前系统时间作为随机种子

    cnt = 0;
    while(cnt < N) {
        random_major = rand() % 2;

        if(random_major) {
            random_no = rand() % (N2 - N1 + 1) + N1;
            printf("20248329%04d\n", random_no);
        }
        else {
            random_no = rand() % N3 + 1;
            printf("20248395%04d\n", random_no);
        }

        cnt++;
    }

    return 0;
}