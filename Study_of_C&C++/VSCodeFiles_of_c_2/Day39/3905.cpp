#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 定义二叉树节点
struct TreeNode
{
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

// 先序递归构建二叉树
void CreateBiTree(TreeNode *&T, const string &s, int &index)
{
    if (index >= (int)s.length() || s[index] == '#')
    {
        T = nullptr;
        index++;
        return;
    }

    T = new TreeNode(s[index]);
    index++;
    CreateBiTree(T->left, s, index);
    CreateBiTree(T->right, s, index);
}

// 非递归中序遍历
void InOrderTraverse(TreeNode *T)
{
    stack<TreeNode *> S;
    TreeNode *p = T;

    while (p != nullptr || !S.empty())
    {
        if (p != nullptr)
        {
            S.push(p);
            p = p->left; // 一直向左，并将沿途节点压入栈中
        }
        else
        {
            p = S.top();
            S.pop();
            cout << p->val << " "; // 访问节点
            p = p->right;          // 转向右子树
        }
    }
    cout << endl;
}

int main()
{
    string preorder_str;
    cout << "请输入带'#'的先序遍历字符串: ";
    cin >> preorder_str;

    TreeNode *root = nullptr;
    int index = 0;
    CreateBiTree(root, preorder_str, index);

    cout << "非递归中序遍历结果: ";
    InOrderTraverse(root);

    return 0;
}
