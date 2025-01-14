#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void appendNode(ListNode *&head, int newValue)
{
    ListNode *newNode = new ListNode(newValue); // 创建新节点
    if (head == nullptr)
    {
        // 如果链表为空，新节点成为头节点
        head = newNode;
    }
    else
    {
        ListNode *current = head;
        // 遍历链表找到最后一个节点
        while (current->next != nullptr)
        {
            current = current->next;
        }
        // 让最后一个节点的 next 指针指向新节点
        current->next = newNode;
    }
}

int main()
{
    ListNode *head = nullptr; // 初始化链表为空
    appendNode(head, 1);      // 添加第一个节点
    appendNode(head, 2);      // 添加第二个节点
    appendNode(head, 3);      // 添加第三个节点

    // 打印链表以验证
    ListNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // 注意：这里省略了释放链表内存的代码，实际使用时应该避免内存泄漏
}