#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> myv;
    myv.push_back(1);
    myv.push_back(2);
    myv.push_back(3);
    vector<int>::iterator it; // �������������it
    for (it = myv.begin(); it != myv.end(); ++it)
        // ��ͷ��β��������Ԫ��
        printf("%d ", *it); // �����1 2 3
    printf("\n");
    vector<int>::reverse_iterator rit;
    // ���巴�������rit
    for (rit = myv.rbegin(); rit != myv.rend(); ++rit)
        // ��β��ͷ��������Ԫ��
        printf("%d ", *rit); // �����3 2 1
    printf("\n");
    return 0;
}