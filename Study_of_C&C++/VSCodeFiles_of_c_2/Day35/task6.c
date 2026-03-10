#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define M 100

typedef struct
{
    int id;
    char name[20];
    char class[100];
} STU;

void shuffle(char *str[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char *temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void sort(char *str[], int n)
{
    STU stu[M];
    for (int i = 0; i < n; i++)
    {
        if (sscanf(str[i], "%d\t%s\t%s", &stu[i].id, stu[i].name, stu[i].class) != 3)
        {
            printf("Error parsing string: %s\n", str[i]);
            return;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (stu[i].id > stu[j].id)
            {
                STU temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        snprintf(str[i], M, "%d\t%s\t%s", stu[i].id, stu[i].name, stu[i].class);
    }
}

void save_to_file(char *str[], int n)
{
    printf("# press \"c\" to set a custom file name\n");
    printf("# press any other key to use default file name\n\n");
    printf("choice: ");
    char choice;
    char filename[100];
    FILE *fp;
    scanf(" %c", &choice);

    if (choice == 'c')
    {
        printf("enter a file name: ");
        scanf("%99s", filename);
        fp = fopen(filename, "w");
    }
    else
    {
        time_t t = time(NULL);
        strftime(filename, sizeof(filename), "%Y-%m-%d_%H-%M-%S.txt", localtime(&t));
        fp = fopen(filename, "w");
    }

    if (fp == NULL)
    {
        printf("\nfail to open\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (fprintf(fp, "%s\n", str[i]) < 0)
        {
            printf("Error\n");
            break;
        }
    }

    fclose(fp);
    printf("\nfile saved as %s\n", filename);
}

int main()
{
    FILE *fp = fopen("list.txt", "r");
    if (fp == NULL)
    {
        printf("fail to open\n");
        return 1;
    }

    char *data[M];
    int cnt = 0;

    while (cnt < M && !feof(fp))
    {
        data[cnt] = malloc(M * sizeof(char));
        if (fgets(data[cnt], M, fp) != NULL)
        {
            data[cnt][strcspn(data[cnt], "\n")] = 0;
            cnt++;
        }
        else
        {
            free(data[cnt]);
            cnt--;
        }
    }
    fclose(fp);

    srand(time(NULL));
    shuffle(data, cnt);

    printf("---------\tRandom Picking\t---------\n\n");
    char *picked[5];
    for (int i = 0; i < 5; i++)
        picked[i] = data[i];

    sort(picked, 5);

    for (int i = 0; i < 5; i++)
        printf("%s\n", picked[i]);

    printf("\n\n---------\tSave to File\t---------\n\n");

    save_to_file(picked, 5);

    for (int i = 0; i < cnt; i++)
        free(data[i]);

    return 0;
}
