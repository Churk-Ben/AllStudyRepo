#include <stdio.h>
#include <string.h>
#define N 10
#define M 80

typedef struct
{
    char name[M];   // 书名
    char author[M]; // 作者
} Book;

int main()
{
    Book x[N] = {{"《一九八四》", "乔治.奥威尔"},
                 {"《美丽新世界》", "赫胥黎"},
                 {"《昨日的世界》", "斯蒂芬.茨威格"},
                 {"《万历十五年》", "黄仁宇"},
                 {"《一只特立独行的猪》", "王小波"},
                 {"《百年孤独》", "马尔克斯"},
                 {"《查令十字街84号》", "海莲.汉芙"},
                 {"《只是孩子》", "帕蒂.史密斯"},
                 {"《刀锋》", "毛姆"},
                 {"《沉默的大多数》", "王小波"}};
    Book *ptr;
    int i;
    char author[M];
    int found;

    // 使用指针遍历结构体数组
    printf("-------------------所有图书信息-------------------\n");
    for (ptr = x; ptr < x + N; ++ptr)
        printf("%-30s%-30s\n", ptr->name, ptr->author);

    // 查找指定作者的图书
    printf("\n-------------------按作者查询图书-------------------\n");
    printf("输入作者名: ");
    gets(author);
    found = 0;
    for (ptr = x; ptr < x + N; ++ptr)
        if (strcmp(ptr->author, author) == 0)
        {
            found = 1;
            printf("%-30s%-30s\n", ptr->name, ptr->author);
        }

    if (!found)
        printf("暂未收录该作者书籍!\n");

    return 0;
}