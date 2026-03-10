#include "Fraction.h"
#include <iostream>
#include <numeric>

const std::string Fraction::doc{"a simplified fraction class"};

Fraction::Fraction(int u) : up{u}, down{1} {}
Fraction::Fraction(int u, int d) : up{u}, down{d}
{
    if (down < 0)
    {
        up = -up;
        down = -down;
    }
    simplify();
}
Fraction::Fraction(const Fraction &f) : up{f.up}, down{f.down} {}

int Fraction::get_up() const { return up; }
int Fraction::get_down() const { return down; }

Fraction Fraction::negative() const
{
    return Fraction(-up, down);
}

void Fraction::simplify()
{
    int g = std::gcd(up, down);
    if (g != 0)
    {
        up /= g;
        down /= g;
    }
}

void output(const Fraction &f)
{
    if (f.down == 0)
    {
        std::cout << "分母不能为0";
    }
    else if (f.down == 1)
    {
        std::cout << f.up;
    }
    else
    {
        std::cout << f.up << "/" << f.down;
    }
}

Fraction add(const Fraction &a, const Fraction &b)
{
    return Fraction(a.up * b.down + b.up * a.down, a.down * b.down);
}

Fraction sub(const Fraction &a, const Fraction &b)
{
    return Fraction(a.up * b.down - b.up * a.down, a.down * b.down);
}

Fraction mul(const Fraction &a, const Fraction &b)
{
    return Fraction(a.up * b.up, a.down * b.down);
}

Fraction div(const Fraction &a, const Fraction &b)
{
    if (b.up == 0)
        return Fraction(1, 0); // 分母为0
    return Fraction(a.up * b.down, a.down * b.up);
}
