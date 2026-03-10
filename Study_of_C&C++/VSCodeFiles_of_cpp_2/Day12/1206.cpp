#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

unsigned char func(unsigned char c);

void test1();
void test2();

int main()
{
    std::cout << "²âÊÔ1: ×Ö·û´®´óÐ¡Ð´×ª»»\n";
    test1();
    std::cout << "\n²âÊÔ2: ×Ö·û±ä»»\n";
    test2();
}

unsigned char func(unsigned char c)
{
    if (c == 'z')
        return 'a';
    if (c == 'Z')
        return 'A';
    if (std::isalpha(c))
        return static_cast<unsigned char>(c + 1);
    return c;
}

void test1()
{
    std::string s1{"Hello World 2049!"};
    std::cout << "s1 = " << s1 << '\n';
    std::string s2;
    for (auto c : s1)
        s2 += std::tolower(c);
    std::cout << "s2 = " << s2 << '\n';
    std::string s3;
    for (auto c : s1)
        s3 += std::toupper(c);
    std::cout << "s3 = " << s3 << '\n';
}

void test2()
{
    std::string s1{"I love cosmos!"};
    std::cout << "s1 = " << s1 << '\n';
    std::string s2(s1.size(), ' ');
    std::transform(s1.begin(), s1.end(), s2.begin(), func);
    std::cout << "s2 = " << s2 << '\n';
}
