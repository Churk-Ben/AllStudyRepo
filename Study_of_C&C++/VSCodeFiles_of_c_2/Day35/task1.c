// �ļ���д��������ʽ������д�ı��ļ�
#include <stdio.h>

#define N 80
#define M 100

typedef struct {
    char name[N];       // ����
    char author[N];     // ����
} Book;

void write();
void read();

int main() {
    printf("����1: ��ͼ����Ϣд���ı��ļ�\n");
    write();

    printf("\n����2: ���ı��ļ���ȡͼ����Ϣ, ��ӡ�������Ļ\n");
    read();

    return 0;
}

void write() {
    Book x[] = { {"�����ܼҡ�", "˹����.����͵�"},
                  {"��������", "����˹���.�Ĳ���"},
	              {"���˵ľ����ԡ�", "���Ѷ�.Լ����"}, 
				  {"������ͣ�����������.������´���", "��˹����.ɳ����"},
				  {"�����֮�ϡ�", "�����١���˹����"}, 
                  {"����ѧ�ǡ�", "������"}, 
                  {"�����ˡ�", "�̳��"} };
    int n, i;
	FILE *fp;

    // ��������x��Ԫ�ظ���
    n = sizeof(x) / sizeof(x[0]);       
	
	// ��д�ķ�ʽ���ı��ļ�data1.txt 
	fp = fopen("data1.txt", "w");
	
	// ������ļ�ʧ�ܣ������ʾ��Ϣ������ 
	if(fp == NULL) {
		printf("fail to open file to write\n");
		return;
	}
	
	// ���ṹ������x�е�ͼ����Ϣ��ʽ��д��fpָ����ļ�data1.txt
	for(i = 0; i < n; ++i)
		fprintf(fp, "%-40s %-20s\n", x[i].name, x[i].author);
	
	fclose(fp);
}

void read() {
    Book x[M]; 
	int i, n;
    int number;
	
	FILE *fp;
	
	// �Զ��ķ�ʽ���ı��ļ�data1.txt 
	fp = fopen("data1.txt", "r");
	
	// ������ļ�ʧ�ܣ������ʾ��Ϣ������ 
	if(fp == NULL) {
		printf("fail to open file to read\n");
		return;
	}
	
    // ���ļ��ж�ȡͼ����Ϣ�����浽�ṹ������x��
   i = 0;
	while(!feof(fp)) {
        number = fscanf(fp, "%s%s", x[i].name, x[i].author);
        if(number != 2)
            break;
        i++;
    }
    n = i;

    // ��ͼ����Ϣ��ӡ�������Ļ��
    for(i = 0; i < n; ++i)
        printf("%d. %-40s%-20s\n", i+1, x[i].name, x[i].author);
	
	fclose(fp);
}