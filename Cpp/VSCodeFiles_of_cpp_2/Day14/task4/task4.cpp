#include "Fraction.h"
#include <iostream>

void test1();
void test2();

int main()
{
    std::cout << "²âÊÔ1: FractionÀà»ù´¡¹¦ÄÜ²âÊÔ\n";
    test1();

    std::cout << "\n²âÊÔ2: ·ÖÄ¸Îª0²âÊÔ: \n";
    test2();
}

void test1()
{
    using std::cout;
    using std::endl;

    cout << "FractionÀà²âÊÔ: " << endl;
    cout << Fraction::doc << endl
         << endl;

    Fraction f1(5);
    Fraction f2(3, -4), f3(-18, 12);
    Fraction f4(f3);
    cout << "f1 = ";
    output(f1);
    cout << endl;
    cout << "f2 = ";
    output(f2);
    cout << endl;
    cout << "f3 = ";
    output(f3);
    cout << endl;
    cout << "f4 = ";
    output(f4);
    cout << endl;

    const Fraction f5(f4.negative());
    cout << "f5 = ";
    output(f5);
    cout << endl;
    cout << "f5.get_up() = " << f5.get_up()
         << ", f5.get_down() = " << f5.get_down() << endl;

    cout << "f1 + f2 = ";
    output(add(f1, f2));
    cout << endl;
    cout << "f1 - f2 = ";
    output(sub(f1, f2));
    cout << endl;
    cout << "f1 * f2 = ";
    output(mul(f1, f2));
    cout << endl;
    cout << "f1 / f2 = ";
    output(div(f1, f2));
    cout << endl;
    cout << "f4 + f5 = ";
    output(add(f4, f5));
    cout << endl;
}

void test2()
{
    using std::cout;
    using std::endl;

    Fraction f6(42, 55), f7(0, 3);
    cout << "f6 = ";
    output(f6);
    cout << endl;
    cout << "f7 = ";
    output(f7);
    cout << endl;
    cout << "f6 / f7 = ";
    output(div(f6, f7));
    cout << endl;
}