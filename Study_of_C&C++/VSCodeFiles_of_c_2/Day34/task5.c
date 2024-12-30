#include <stdio.h>
#include <math.h>// ��������͵͵���˸�math��

typedef struct
{
    int year;
    int month;
    int day;
} Date;

// ��������
void input(Date *pd);                // �������ڸ�pdָ���Date����
int day_of_year(Date d);             // ��������d����һ��ĵڶ�����
int compare_dates(Date d1, Date d2); // �Ƚ���������:
                                     // ���d1��d2֮ǰ������-1;
                                     // ���d1��d2֮�󣬷���1
                                     // ���d1��d2��ͬ������0

void test1()
{
    Date d;
    int i;

    printf("��������:(������2024-12-16��������ʽ����)\n");
    for (i = 0; i < 3; ++i)
    {
        input(&d);
        printf("%d-%02d-%02d����һ���е�%d��\n\n", d.year, d.month, d.day, day_of_year(d));
    }
}

void test2()
{
    Date Churk_birth, Chloris_birth;
    int i;
    int ans;

    printf("����Churk��Chloris��������:(������2024-12-16��������ʽ����)\n");
    for (i = 0; i < 3; ++i)
    {
        input(&Churk_birth);
        input(&Chloris_birth);
        ans = compare_dates(Churk_birth, Chloris_birth);

        if (ans == 0)
            printf("Churk��Chlorisһ����\n\n");
        else if (ans == -1)
            printf("Churk��Chloris��\n\n");
        else
            printf("Churk��ChlorisС\n\n");
    }
}

int main()
{
    printf("����1: ��������, ��ӡ�������һ���еڶ�����\n");
    test1();

    printf("\n����2: �����������С��ϵ\n");
    test2();
}

// ���㺯��inputʵ��
// ����: �������ڸ�pdָ���Date����
void input(Date *pd)
{
    scanf("%d-%d-%d", &pd->year, &pd->month, &pd->day);
}

// ���㺯��day_of_yearʵ��
// ���ܣ���������d����һ��ĵڶ�����
int day_of_year(Date d)
{
    int days_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;

    if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
        days_of_month[1]++;

    for (int i = 1; i < d.month; i++)
        days += days_of_month[i - 1];

    days += d.day;
    return days;
}

// ���㺯��compare_datesʵ��
// ���ܣ��Ƚ���������:
// ���d1��d2֮ǰ������-1;
// ���d1��d2֮�󣬷���1
// ���d1��d2��ͬ������0
int compare_dates(Date d1, Date d2)// ��������͵͵���˸�math��
{
    int cmp_year = d1.year - d2.year;
    if (cmp_year != 0)
        return cmp_year / abs(cmp_year);

    int cmp_month = d1.month - d2.month;
    if (cmp_month != 0)
        return cmp_month / abs(cmp_month);

    int cmp_day = d1.day - d2.day;
    if (cmp_day != 0)
        return cmp_day / abs(cmp_day);

    return 0;
}