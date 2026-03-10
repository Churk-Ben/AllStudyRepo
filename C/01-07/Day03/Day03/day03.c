#include <stdio.h>

int main()
{
	while (1) {
		int m, s, n = 0, t = 0;
		printf("输入一个整数：");
			scanf_s("%d", &n);
		s = n;
		while (n) {
			m = n % 10;
			t = 10 * t + m;
			n /= 10;
		}
		if (t == s) {
			printf("%d是回文数\n", s);
		}
		else
		{
			printf("%d不是回文数\n", s);
		}
	}

	return 0;
}