#include <stdio.h>
#include <math.h>

char fractal_universe[10000][10000];

void fra_universe(int x, int y, int n) // n��ʾ�Ǽ��ȵķ������棬��x��y����ʾn�ȷ�����������Ͻǵ����ꣻ
{
    int distance = pow(3, n - 2);
    if (n == 1)
    {
        fractal_universe[x][y] = 'X';
        return;
    }
    fra_universe(x, y, n - 1); // ��x��y����ʾn�ȵķ�������ͼ�ε����Ͻǵ�n-1�ȷ�������ͼ�ε����Ͻ�����

    fra_universe(x + 2 * distance, y, n - 1); // ��x + 2 * distance,y����ʾn�ȵķ�������ͼ�ε����Ͻǵ�n-1�ȷ�������ͼ�ε����Ͻǵ����ꣻ

    fra_universe(x + distance, y + distance, n - 1); // ��x + distance, y + distance����ʾn�ȵķ�������ͼ�ε��м��n-1�ȷ�������ͼ�ε����Ͻ�����

    fra_universe(x, y + 2 * distance, n - 1); //(x, y + 2 * distance)��ʾn�ȵķ�������ͼ�ε����½ǵ�n-1�ȵķ�������ͼ�ε����Ͻǵ�����

    fra_universe(x + 2 * distance, y + 2 * distance, n - 1); // ��x + 2 * distance, y + 2 * distance����ʾn�ȵķ�������ͼ�ε����½ǵ�n-1�ȷ�������ͼ�ε����Ͻ�����
}

int main()
{
    int n;
    scanf("%d", &n);
    int size = pow(3, n - 1);
    fra_universe(0, 0, n);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (fractal_universe[i][j] != 'X')
            {
                fractal_universe[i][j] = ' ';
            }
            printf("%c", fractal_universe[i][j]);
        }
        printf("\n");
    }

    return 0;
}

//https://blog.csdn.net/mili_j/article/details/130273454