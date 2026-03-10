// 文件读写操作：以字符、字符串形式读、写

#include <stdio.h>
#define N 5
#define M 80

void write();
void read_str();
void read_char();

int main() {
    printf("测试1: 把一组字符信息以字符串方式写入文本文件\n");
    write();

    printf("\n测试2: 从文件以字符串方式读取, 输出到屏幕\n");
    read_str();

    printf("\n测试3: 从文件以单个字符方式读取, 输出到屏幕\n");
    read_char();

    return 0;
}

void write() {
    char *ptr[N] = { "Working\'s Blues",
                     "Everything Will Flow",
                     "Streets of London",
                     "Perfect Day",
                     "Philadelphia"};
    int i;
    FILE *fp;

    fp = fopen("data3.txt", "w");
    if(!fp) {
        printf("fail to open file to write\n");
        return;
    }

    for(i = 0; i < N; ++i) {
        fputs(ptr[i], fp);
        fputs("\n", fp);
    }
    
    fclose(fp);
}

void read_str() {
    char songs[N][M];
    int i;
    FILE *fp;

    fp = fopen("data3.txt", "r");
    if(!fp) {
        printf("fail to open file to read\n");
        return;
    }

    for(i = 0; i < N; ++i)
        fgets(songs[i], 80, fp);

    for(i = 0; i < N; ++i)
        printf("%d. %s", i+1, songs[i]);
    
    fclose(fp);
}

void read_char() {
    char ch;
    FILE *fp;

    fp = fopen("data3.txt", "r");
    if(!fp) {
        printf("fail to open file to read\n");
        return;
    }

    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == EOF)
            break;
        
        putchar(ch);
    }

    fclose(fp);
}