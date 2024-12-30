// P286��8.17
// �Խ̲�ʾ����������΢���������ѧ����Ϣ������д��һ������ģ��
// ��ӡ������ѧ����Ϣ����ӡ����ѧ����Ϣ�����ø�ģ��ʵ��

#include <stdio.h>
#include <string.h>
#define N 2 // ���г����������ʱ�����԰�N��СһЩ�������

typedef struct student
{
	int id;			  // ѧ��
	char name[20];	  // ����
	char subject[20]; // ���Կ�Ŀ
	double perf;	  // ƽʱ�ɼ�
	double mid;		  // ���гɼ�
	double final;	  // ��ĩ�ɼ�
	double total;	  // �����ɼ�
	char level[10];	  // �ɼ��ȼ�
} STU;

void input(STU[], int);		 // ¼��ѧ����Ϣ
void output(STU[], int);	 // ���ѧ����Ϣ
void calc(STU[], int);		 // ���������͵ȼ�
int fail(STU[], STU[], int); // ͳ�Ʋ�����ѧ����Ϣ
void sort(STU[], int);		 // ����

int main()
{
	STU st[N], fst[N]; // ����st��¼ѧ����Ϣ��fst��¼������ѧ����Ϣ
	int k;			   // ���ڼ�¼������ѧ������

	printf("¼��ѧ���ɼ���Ϣ:\n");
	input(st, N);

	printf("\n�ɼ�����...\n");
	calc(st, N);

	k = fail(st, fst, N);
	sort(st, N);
	printf("\nѧ���ɼ��������:\n");
	output(st, N);

	printf("\n������ѧ����Ϣ:\n");
	output(fst, k);

	return 0;
}

void input(STU s[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		scanf("%d %s %s %lf %lf %lf", &s[i].id, s[i].name, s[i].subject,
			  &s[i].perf, &s[i].mid, &s[i].final);
}

void output(STU s[], int n)
{
	int i;

	printf("-----------------\n");
	printf("ѧ��   ����     ��Ŀ   ƽʱ   ����   ��ĩ   ����   �ȼ�\n");
	for (i = 0; i < n; i++)
		printf("%d   %-6s   %-4s   %-4.0f   %-4.0f   %-4.0f   %-4.1f   %s\n", s[i].id, s[i].name, s[i].subject, s[i].perf, s[i].mid, s[i].final, s[i].total, s[i].level);
}

void calc(STU s[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		s[i].total = s[i].perf * 0.2 +
					 s[i].mid * 0.2 +
					 s[i].final * 0.6;

		if (s[i].total >= 90)
			strcpy(s[i].level, "��");
		else if (s[i].total >= 80)
			strcpy(s[i].level, "��");
		else if (s[i].total >= 70)
			strcpy(s[i].level, "��");
		else if (s[i].total >= 60)
			strcpy(s[i].level, "����");
		else
			strcpy(s[i].level, "������");
	}
}

int fail(STU s[], STU t[], int n)
{
	int i, cnt = 0;

	for (i = 0; i < n; i++)
		if (s[i].total < 60)
			t[cnt++] = s[i];

	return cnt;
}

void sort(STU s[], int n)
{
	int i, j;
	STU t;

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - 1 - i; j++)
			if (s[j].total < s[j + 1].total)
			{
				t = s[j];
				s[j] = s[j + 1];
				s[j + 1] = t;
			}
}