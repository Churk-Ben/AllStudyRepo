// 文件读写操作：格式化读、写文本文件
#include <stdio.h>

#define N 80
#define M 100

typedef struct {
    char name[N];       // 书名
    char author[N];     // 作者
} Book;

void write();
void read();

int main() {
    printf("测试1: 把图书信息写入文本文件\n");
    write();

    printf("\n测试2: 从文本文件读取图书信息, 打印输出到屏幕\n");
    read();

    return 0;
}

void write() {
    Book x[] = { {"《雕塑家》", "斯科特.麦克劳德"},
                  {"《灯塔》", "克里斯多夫.夏布特"},
	              {"《人的局限性》", "塞缪尔.约翰生"}, 
				  {"《永不停步：玛格丽特.阿特伍德传》", "罗斯玛丽.沙利文"},
				  {"《大地之上》", "罗欣顿·米斯特里"}, 
                  {"《上学记》", "何兆武"}, 
                  {"《命运》", "蔡崇达"} };
    int n, i;
	FILE *fp;

    // 计算数组x中元素个数
    n = sizeof(x) / sizeof(x[0]);       
	
	// 以写的方式打开文本文件data1.txt 
	fp = fopen("data1.txt", "w");
	
	// 如果打开文件失败，输出提示信息并返回 
	if(fp == NULL) {
		printf("fail to open file to write\n");
		return;
	}
	
	// 将结构体数组x中的图书信息格式化写到fp指向的文件data1.txt
	for(i = 0; i < n; ++i)
		fprintf(fp, "%-40s %-20s\n", x[i].name, x[i].author);
	
	fclose(fp);
}

void read() {
    Book x[M]; 
	int i, n;
    int number;
	
	FILE *fp;
	
	// 以读的方式打开文本文件data1.txt 
	fp = fopen("data1.txt", "r");
	
	// 如果打开文件失败，输出提示信息并返回 
	if(fp == NULL) {
		printf("fail to open file to read\n");
		return;
	}
	
    // 从文件中读取图书信息，保存到结构体数组x中
   i = 0;
	while(!feof(fp)) {
        number = fscanf(fp, "%s%s", x[i].name, x[i].author);
        if(number != 2)
            break;
        i++;
    }
    n = i;

    // 将图书信息打印输出到屏幕上
    for(i = 0; i < n; ++i)
        printf("%d. %-40s%-20s\n", i+1, x[i].name, x[i].author);
	
	fclose(fp);
}