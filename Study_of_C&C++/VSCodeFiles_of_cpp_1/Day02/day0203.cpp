#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      double length;   // ����
      double breadth;  // ���
      double height;   // �߶�
      // ��Ա��������
      double get(void);
      void set( double len, double bre, double hei );
};
// ��Ա��������
double Box::get(void)
{
    return length * breadth * height;
}
 
void Box::set( double len, double bre, double hei)
{
    length = len;
    breadth = bre;
    height = hei;
}
int main( )
{
   Box Box1;        // ���� Box1������Ϊ Box
   Box Box2;        // ���� Box2������Ϊ Box
   double volume = 0.0;     // ���ڴ洢���
 
   // box 1 ����
   Box1.height = 5.0; 
   Box1.length = 6.0; 
   Box1.breadth = 7.0;
    
 
   // box 1 �����
   volume = Box1.height * Box1.length * Box1.breadth;
   cout << "Box1 �ĵ�ַ��" << &Box1 <<endl;
   cout << "Box1 �������" << volume <<endl;
 
   // box 2 ����
   volume = Box2.get(); 
   cout << "Box2 �ĵ�ַ��" << &Box2 <<endl;
   cout << "Box2 �������" << volume <<endl;
    
   Box2 = Box1;
   volume = Box2.get();
   cout << "Box2 �ĵ�ַ��" << &Box2 <<endl;
   cout << "Box2 �������" << volume <<endl;
   return 0;
}