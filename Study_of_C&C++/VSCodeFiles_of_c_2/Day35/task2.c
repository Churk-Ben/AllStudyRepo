// �ļ���д�����������ݿ鷽ʽ����д�������ļ�

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
    printf("����1: ��ͼ����Ϣ�����ݿ鷽ʽд��������ļ�\n");
    write();

    printf("\n����2: �Ӷ������ļ���ȡͼ����Ϣ, ��ӡ�������Ļ\n");
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
    int n;
	FILE *fp;

    // ��������x��Ԫ�ظ���
    n = sizeof(x) / sizeof(x[0]);     
	
	// ��д�ķ�ʽ�򿪶������ļ�data2.dat
	fp = fopen("data2.dat", "wb");
	
	// ������ļ�ʧ�ܣ������ʾ��Ϣ������ 
	if(fp == NULL) {
		printf("fail to open file to write\n");
		return;
	}
	
	// ���ṹ������x�е�ͼ����Ϣ�����ݿ鷽ʽд��������ļ�data2.dat
    fwrite(x, sizeof(Book), n, fp);
	
	fclose(fp);
}

void read() {
    Book x[M]; 
	int i, n;
    int number;
	
	FILE *fp;
	
	// �Զ��ķ�ʽ�򿪶������ļ�data2.dat
    fp = fopen("data2.dat", "rb");
	
	// ������ļ�ʧ�ܣ������ʾ��Ϣ������ 
	if(fp == NULL) {
		printf("fail to open file to read\n");
		return;
	}
	
    // �Ӷ������ļ�data2.dat�����ݿ鷽ʽ��ȡͼ����Ϣ�洢���ṹ������x
    i = 0;
    while(!feof(fp)) {
        number = fread(&x[i], sizeof(Book), 1, fp);
        if(number != 1)
            break;
        i++;
    }

    // ����Ļ�ϴ�ӡ���
    n = i;
    for(i = 0; i < n; ++i)
        printf("%d. %-40s%-20s\n", i+1, x[i].name, x[i].author);
    
	fclose(fp);
}
