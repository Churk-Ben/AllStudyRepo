#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 100 // 假设文件最多有100行
#define MAX_LENGTH 100 // 假设每行最多100个字符

void shuffle(char *array[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    FILE *file = fopen("..\\list.txt", "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    char *data[MAX_LINES];
    int count = 0;

    // 读取文件中的数据
    while (count < MAX_LINES && !feof(file)) {
        data[count] = malloc(MAX_LENGTH * sizeof(char));
        if (fgets(data[count], MAX_LENGTH, file) != NULL) {
            // 去除换行符
            data[count][strcspn(data[count], "\n")] = 0;
            count++;
        }
    }
    fclose(file);

    // 如果文件中的数据少于5个
    if (count < 5) {
        printf("文件中的数据点不足5个。\n");
        return 1;
    }

    // 随机打乱数据顺序
    srand(time(NULL));
    shuffle(data, count);

    // 打印前5个互不重复的数据点
    printf("随机抽取的五个互不重复的数据点是：\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", data[i]);
        free(data[i]); // 释放分配的内存
    }

    return 0;
}
