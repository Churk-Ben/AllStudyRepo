#include <stdio.h>
#include <string.h>

#define N 10

typedef struct
{
    long id;          // 准考证号
    char name[20];    // 姓名
    float objective;  // 客观题得分
    float subjective; // 操作题得分
    float sum;        // 总分
    char result[10];  // 考试结果
} STU;

// 函数声明
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
    output(stu, N); // 输出所有考生完整信息到屏幕
    write(stu, N);  // 输出考试通过的考生信息到文件

    pass_rate = 1.0 * cnt / N;
    printf("\nPass Rank: %.2f%%\n", pass_rate * 100);

    return 0;
}

// 把所有考生完整信息输出到屏幕上
// 准考证号，姓名，客观题得分，操作题得分，总分，结果
void output(STU st[], int n)
{
    int i;

    printf("Number\tName\tObj_Score\tOpe_Score\tTotal_Score\tResult\n");
    for (i = 0; i < n; i++)
        printf("%ld\t%s\t%.2f\t\t%.2f\t\t%.2f\t\t%s\n", st[i].id, st[i].name, st[i].objective, st[i].subjective, st[i].sum, st[i].result);
}

// 从文本文件examinee.txt读入考生信息:准考证号，姓名，客观题得分，操作题得分
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

// 把通过考试的考生完整信息写入文件list_pass.txt
// 准考证号，姓名，客观题得分，操作题得分，总分，结果
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

// 对考生信息进行处理：计算每位考生考试总分、结果；统计考试通过的人数
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