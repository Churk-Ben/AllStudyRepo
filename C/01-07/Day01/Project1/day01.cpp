#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int n;
	printf("202483290476张正珂");
		srand((unsigned)time(NULL));
	n = rand() % 2024 + 1;
	printf("领取到的铭牌号：%d\n", n);
	return 0;
}