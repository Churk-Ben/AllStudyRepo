#include <stdio.h>

int main()
{
	while (1) {
		int m, s, n = 0, t = 0;
		printf("����һ��������");
			scanf_s("%d", &n);
		s = n;
		while (n) {
			m = n % 10;
			t = 10 * t + m;
			n /= 10;
		}
		if (t == s) {
			printf("%d�ǻ�����\n", s);
		}
		else
		{
			printf("%d���ǻ�����\n", s);
		}
	}

	return 0;
}