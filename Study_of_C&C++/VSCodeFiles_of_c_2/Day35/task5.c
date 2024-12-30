#include <stdio.h>
#include <string.h>

#define N 10

typedef struct
{
    long id;          // ׼��֤��
    char name[20];    // ����
    float objective;  // �͹���÷�
    float subjective; // ������÷�
    float sum;        // �ܷ�
    char result[10];  // ���Խ��
} STU;

// ��������
void read(STU st[], int n);
void write(STU st[], int n);
void output(STU st[], int n);
int process(STU st[], int n, STU st_pass[]);

int main()
{
    STU stu[N], stu_pass[N];
    int cnt;
    double pass_rate;

    printf("Add %d students from file...\n", N);
    read(stu, N);

    printf("\nFiguring...\n");
    cnt = process(stu, N, stu_pass);

    printf("\nStudents passed the exam:\n");
    output(stu, N); // ������п���������Ϣ����Ļ
    write(stu, N);  // �������ͨ���Ŀ�����Ϣ���ļ�

    pass_rate = 1.0 * cnt / N;
    printf("\nPass Rank: %.2f%%\n", pass_rate * 100);

    return 0;
}

// �����п���������Ϣ�������Ļ��
// ׼��֤�ţ��������͹���÷֣�������÷֣��ܷ֣����
void output(STU st[], int n)
{
    int i;

    printf("Number\tName\tObj_Score\tOpe_Score\tTotal_Score\tResult\n");
    for (i = 0; i < n; i++)
        printf("%ld\t%s\t%.2f\t\t%.2f\t\t%.2f\t\t%s\n", st[i].id, st[i].name, st[i].objective, st[i].subjective, st[i].sum, st[i].result);
}

// ���ı��ļ�examinee.txt���뿼����Ϣ:׼��֤�ţ��������͹���÷֣�������÷�
void read(STU st[], int n)
{
    int i;
    FILE *fin;

    fin = fopen("examinee.txt", "r");
    if (!fin)
    {
        printf("fail to open file\n");
        return;
    }

    while (!feof(fin))
    {
        for (i = 0; i < n; i++)
            fscanf(fin, "%ld %s %f %f", &st[i].id, st[i].name, &st[i].objective, &st[i].subjective);
    }

    fclose(fin);
}

// ��ͨ�����ԵĿ���������Ϣд���ļ�list_pass.txt
// ׼��֤�ţ��������͹���÷֣�������÷֣��ܷ֣����
void write(STU st[], int n)
{
    int i, cnt = 0;
    FILE *fp;

    fp = fopen("list_pass.txt", "w");
    if (!fp)
    {
        printf("fail to open file\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (st[i].sum >= 60)
        {
            cnt++;
            fprintf(fp, "%ld %s %.2f %.2f %.2f %s\n", st[i].id, st[i].name, st[i].objective, st[i].subjective, st[i].sum, st[i].result);
        }
    }

    fclose(fp);

    printf("%d students passed the exam\n", cnt);
}

// �Կ�����Ϣ���д�������ÿλ���������ܷ֡������ͳ�ƿ���ͨ��������
int process(STU st[], int n, STU st_pass[])
{
    int i, cnt = 0;

    for (i = 0; i < n; i++)
    {
        st[i].sum = st[i].objective + st[i].subjective;
        if (st[i].sum >= 60)
        {
            cnt++;
            strcpy(st[i].result, "Passed");
            strcpy(st_pass[cnt - 1].name, st[i].name);
            st_pass[cnt - 1].id = st[i].id;
            st_pass[cnt - 1].objective = st[i].objective;
            st_pass[cnt - 1].subjective = st[i].subjective;
            st_pass[cnt - 1].sum = st[i].sum;
            strcpy(st_pass[cnt - 1].result, st[i].result);
        }
        else
        {
            strcpy(st[i].result, "Failed");
        }
    }

    return cnt;
}