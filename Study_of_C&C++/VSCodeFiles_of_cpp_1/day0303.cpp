#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void appendNode(ListNode *&head, int newValue)
{
    ListNode *newNode = new ListNode(newValue); // �����½ڵ�
    if (head == nullptr)
    {
        // �������Ϊ�գ��½ڵ��Ϊͷ�ڵ�
        head = newNode;
    }
    else
    {
        ListNode *current = head;
        // ���������ҵ����һ���ڵ�
        while (current->next != nullptr)
        {
            current = current->next;
        }
        // �����һ���ڵ�� next ָ��ָ���½ڵ�
        current->next = newNode;
    }
}

int main()
{
    ListNode *head = nullptr; // ��ʼ������Ϊ��
    appendNode(head, 1);      // ��ӵ�һ���ڵ�
    appendNode(head, 2);      // ��ӵڶ����ڵ�
    appendNode(head, 3);      // ��ӵ������ڵ�

    // ��ӡ��������֤
    ListNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // ע�⣺����ʡ�����ͷ������ڴ�Ĵ��룬ʵ��ʹ��ʱӦ�ñ����ڴ�й©
}