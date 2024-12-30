#include <stdio.h>

char score_to_grade(int score); // ��������

int main()
{
    int score;
    char grade;

    while (scanf("%d", &score) != EOF)
    {
        grade = score_to_grade(score); // ��������
        printf("����: %d, �ȼ�: %c\n\n", score, grade);
    }

    return 0;
}

// ��������
char score_to_grade(int score)
{
    char ans;

    switch (score / 10)
    {
    case 10:
    case 9:
        ans = 'A';
        break;
    case 8:
        ans = 'B';
        break;
    case 7:
        ans = 'C';
        break;
    case 6:
        ans = 'D';
        break;
    default:
        ans = 'E';
    }

    return ans;
}