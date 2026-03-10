#include <stdio.h>
#define N 10

typedef struct
{
    char isbn[20];      // isbn号
    char name[80];      // 书名
    char author[80];    // 作者
    double sales_price; // 售价
    int sales_count;    // 销售册数
} Book;

void output(Book x[], int n);
void sort(Book x[], int n);
double sales_amount(Book x[], int n);

int main()
{
    Book x[N] = {{"978-7-5327-6082-4", "门将之死", "罗纳德.伦", 42, 51},
                 {"978-7-308-17047-5", "自由与爱之地：入以色列记", "云也退", 49, 30},
                 {"978-7-5404-9344-8", "伦敦人", "克莱格泰勒", 68, 27},
                 {"978-7-5447-5246-6", "软件体的生命周期", "特德姜", 35, 90},
                 {"978-7-5722-5475-8", "芯片简史", "汪波", 74.9, 49},
                 {"978-7-5133-5750-0", "主机战争", "布莱克.J.哈里斯", 128, 42},
                 {"978-7-2011-4617-1", "世界尽头的咖啡馆", "约翰·史崔勒基", 22.5, 44},
                 {"978-7-5133-5109-6", "你好外星人", "英国未来出版集团", 118, 42},
                 {"978-7-1155-0509-5", "无穷的开始:世界进步的本源", "戴维·多伊奇", 37.5, 55},
                 {"978-7-229-14156-1", "源泉", "安.兰德", 84, 59}};

    printf("图书销量排名(按销售册数): \n");
    sort(x, N);
    output(x, N);

    printf("\n图书销售总额: %.2f\n", sales_amount(x, N));

    return 0;
}

// 待补足：函数output()实现
void output(Book x[], int n)
{
    printf("ISBN号\t\t\t 书名\t\t\t\t 作者\t\t\t 售价\t 销售册数\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-15s\t %-25s\t %-20s\t %-5g\t %-5d\n", x[i].isbn, x[i].name, x[i].author, x[i].sales_price, x[i].sales_count);
    }
    // 调死我了这里输出
}

// 待补足：函数sort()实现
void sort(Book x[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (x[i].sales_count < x[j].sales_count)
            {
                Book temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
}

// 待补足：函数sales_amount()实现
double sales_amount(Book x[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += x[i].sales_price * x[i].sales_count;
    }
    return sum;
}
