#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      double length;   // 长度
      double breadth;  // 宽度
      double height;   // 高度
      // 成员函数声明
      double get(void);
      void set( double len, double bre, double hei );
};
// 成员函数定义
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
   Box Box1;        // 声明 Box1，类型为 Box
   Box Box2;        // 声明 Box2，类型为 Box
   double volume = 0.0;     // 用于存储体积
 
   // box 1 详述
   Box1.height = 5.0; 
   Box1.length = 6.0; 
   Box1.breadth = 7.0;
    
 
   // box 1 的体积
   volume = Box1.height * Box1.length * Box1.breadth;
   cout << "Box1 的地址：" << &Box1 <<endl;
   cout << "Box1 的体积：" << volume <<endl;
 
   // box 2 详述
   volume = Box2.get(); 
   cout << "Box2 的地址：" << &Box2 <<endl;
   cout << "Box2 的体积：" << volume <<endl;
    
   Box2 = Box1;
   volume = Box2.get();
   cout << "Box2 的地址：" << &Box2 <<endl;
   cout << "Box2 的体积：" << volume <<endl;
   return 0;
}