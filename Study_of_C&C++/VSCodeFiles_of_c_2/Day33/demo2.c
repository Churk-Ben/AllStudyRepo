#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 100 // �����ļ������100��
#define MAX_LENGTH 100 // ����ÿ�����100���ַ�

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
        perror("�޷����ļ�");
        return 1;
    }

    char *data[MAX_LINES];
    int count = 0;

    // ��ȡ�ļ��е�����
    while (count < MAX_LINES && !feof(file)) {
        data[count] = malloc(MAX_LENGTH * sizeof(char));
        if (fgets(data[count], MAX_LENGTH, file) != NULL) {
            // ȥ�����з�
            data[count][strcspn(data[count], "\n")] = 0;
            count++;
        }
    }
    fclose(file);

    // ����ļ��е���������5��
    if (count < 5) {
        printf("�ļ��е����ݵ㲻��5����\n");
        return 1;
    }

    // �����������˳��
    srand(time(NULL));
    shuffle(data, count);

    // ��ӡǰ5�������ظ������ݵ�
    printf("�����ȡ����������ظ������ݵ��ǣ�\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", data[i]);
        free(data[i]); // �ͷŷ�����ڴ�
    }

    return 0;
}
