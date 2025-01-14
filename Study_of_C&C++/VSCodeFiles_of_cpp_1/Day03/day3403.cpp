
// ȫվ���ݽ���ѧϰ����ֹ��ԭ�Ļ��޸���ʽ����κ���ҵʹ�ã���׼�ء�һ������Ȩ��Э��
// ��Դ:totuma.cn
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

// ��ʼ������
bool List_Init(LinkList &pHead)
{
    pHead = (LNode *)malloc(sizeof(LNode)); // Ϊͷ�������ڴ沢����ַ�洢��pHead�С�
    if (pHead == NULL)
        return false;   // ����ڴ�����Ƿ�ɹ���pHead��ΪNULL����
    pHead->next = NULL; // ��ʼ��ͷ����'next'ָ��ΪNULL����Ϊ����������Ψһ�Ľڵ㡣
    return true;
}

// �жϵ������Ƿ�Ϊ��
bool List_Empty(LinkList pHead)
{
    return pHead->next == NULL; // ���ͷ����'next'ָ���Ƿ�ΪNULL������ǣ�������Ϊ�ա�
}

// ��ȡ��������Ч���ݽڵ����
int List_Length(LinkList pHead)
{
    int count = 0;                                       // ���ڼ�����Ч�ڵ�ı���
    for (LNode *p = pHead->next; p != NULL; p = p->next) // ��ͷ������һ���ڵ㿪ʼ����������ֱ������������ڵ�ΪNULL����
        count++;                                         // ÿ����һ���ڵ㣬��Ч�ڵ�������1��
    return count;
}

// totuma.cn
// ��������ͷ�巨���Ϊ����
LinkList List_Create(LinkList &pHead)
{
    LNode *pTemp;
    int x; // ��ʱ�ڵ�ָ��
    scanf("%d", &x);
    while (x != 999)
    {
        pTemp = (LNode *)malloc(sizeof(LNode)); // �����ڴ沢�����½ڵ�
        pTemp->data = x;
        pTemp->next = pHead->next; // �½ڵ��ָ��ָ��ǰͷ�ڵ����һ���ڵ�
        pHead->next = pTemp;       // ͷָ��ָ���½ڵ㣬ʹ���Ϊ�µ�ͷ�ڵ�
        scanf("%d", &x);
    }
    return pHead; // ���ش�ͷ��������ͷָ��
}

// totuma.cn
// ��������-ͨ��β�巨
LinkList List_Create_Tail_Insert(LinkList &pHead)
{
    LNode *pTemp;         // ��ʱ�ڵ�ָ��
    LNode *pTail = pHead; // β�ڵ�ָ�룬��ʼָ��ͷ���
    int x;                // ���ڴ洢���������
    scanf("%d", &x);
    while (x != 999)
    {
        pTemp = (LNode *)malloc(sizeof(LNode)); // �����ڴ沢�����½ڵ�
        pTemp->data = x;                        // β�ڵ����һ��ָ��ָ���½ڵ�
        pTail->next = pTemp;                    // ����β�ڵ�ָ�룬ʹ��ָ���½ڵ�
        pTail = pTemp;                          // ��ȡ��һ������
        scanf("%d", &x);
    }
    pTail->next = NULL; // β�ڵ����һ��ָ����Ϊ NULL����ʾ�������
    return pHead;       // ���ش�ͷ��������ͷָ��
}

// totuma.cn
// ��λ����룬i=1���ڱ�ͷ��i=length+1���ڱ�β
bool List_Insert(LinkList &pHead, int i, int e)
{
    if (i < 1 || i > List_Length(pHead) + 1)
        return false; // ������λ���Ƿ���Ч
    int j = 0;        // ��ǰpָ����ǵڼ������
    LNode *p = pHead; // p ָ��ͷ���
    while (p != NULL && j < i - 1)
    { // ѭ���ҵ�Ҫ����λ�õ�ǰ����㣬ֱ���ҵ�ǰ���������������
        p = p->next;
        j++;
    }
    LNode *pTemp = (LNode *)malloc(sizeof(LNode));
    pTemp->data = e;
    pTemp->next = p->next; // ���½ڵ��'next'ָ��p����һ���ڵ�
    p->next = pTemp;       // ����p��'next'ָ���½ڵ㣬��ɲ��������
    return true;
}

// totuma.cn
// ͨ��ֵ��ȡ������λ��
LNode *List_Get_Elem(LinkList pHead, int e, int &i)
{
    i = 1;
    LNode *p = pHead->next; // pָ���һ�����ݽڵ�
    while (p != NULL && p->data != e)
    {
        p = p->next;
        i = i + 1;
    }
    return p;
}

// totuma.cn
// ��λ��ɾ����i=1ɾ��ͷ��i=lengthɾͷβ
bool List_Del(LinkList &pHead, int i)
{
    if (i < 1 || i > List_Length(pHead))
        return false;
    LNode *p = pHead;
    // �ҵ���ɾ��λ���ǰһλ��㣬i==1�Ѵ����ʴ�j=2��ʼ
    for (int j = 0; j < i - 1; j++)
        p = p->next;
    LNode *q = p->next; // ��ɾ�����
    p->next = q->next;  // q->next p p->next ����p
    free(q);
    return true;
}

// totuma.cn
// ��ӡ��������ֵ
void List_Show(LinkList pHead)
{
    LNode *node = pHead->next;
    printf("����ֵ��");
    while (node != NULL)
    {
        printf("%d��", node->data);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    LinkList pHead;
    List_Init(pHead);
    printf("�����пգ�%s\n", List_Empty(pHead) ? "��" : "�ǿ�");

    // ͷ�巨����
    List_Create(pHead);
    List_Show(pHead);
    printf("�����ȣ�%d\n\n", List_Length(pHead));

    printf("λ��Ϊ1(ͷ��)�����룺0\n");
    List_Insert(pHead, 1, 0);
    List_Show(pHead);
    printf("�����ȣ�%d\n\n", List_Length(pHead));

    printf("λ��Ϊ%d(β��)�����룺99\n", List_Length(pHead) + 1);
    List_Insert(pHead, List_Length(pHead) + 1, 99);
    List_Show(pHead);
    printf("�����ȣ�%d\n\n", List_Length(pHead));

    printf("ɾ��λ��Ϊ1(ͷɾ)\n");
    List_Del(pHead, 1);
    List_Show(pHead);
    printf("�����ȣ�%d\n\n", List_Length(pHead));

    printf("ɾ��λ��Ϊ%d(βɾ)\n", List_Length(pHead));
    List_Del(pHead, List_Length(pHead));
    List_Show(pHead);
    printf("�����ȣ�%d\n\n", List_Length(pHead));

    printf("��ȡֵΪ��5�Ľ��λ��\n");
    int i = -1; // -1 Ϊδ�ҵ�
    LNode *p5 = List_Get_Elem(pHead, 5, i);
    printf("ֵΪ5�Ľ��λ��Ϊ��%d\n\n", p5 != NULL ? i : -1);

    printf("�����пգ�%s\n", List_Empty(pHead) ? "��" : "�ǿ�");

    // β�巨����
    LinkList pHead1;
    List_Init(pHead1);

    List_Create_Tail_Insert(pHead1);
    printf("β�巨��������\n");
    List_Show(pHead1);
    return 0;
}