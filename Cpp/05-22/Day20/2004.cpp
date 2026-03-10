#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(string n) : name(n) {}

    ~Person() { cout << "P"; }

private:
    string name;
};

class Date
{
public:
    Date(int y = 2023, int m = 2, int d = 13) : year(y), month(m), day(d) {}

    ~Date()
    {
        cout << 'D';
    }

private:
    int year, month, day;
};

class Staff : public Person
{
public:
    Staff(string n, int y, int m, int d, char c) : birthday(y, m, d), sex(c), Person(n) {}
    ~Staff()
    {
        cout << 'S';
    }

private:
    Date birthday;
    char sex;
};

int main()
{
    Staff *p = new Staff("Wang", 2001, 11, 9, 'M');
    delete p;
    return 0;
}
