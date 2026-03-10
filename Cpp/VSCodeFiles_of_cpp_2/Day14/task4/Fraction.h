#pragma once
#include <string>

class Fraction
{
public:
    static const std::string doc;

    Fraction(int up);
    Fraction(int up, int down);
    Fraction(const Fraction &f);

    int get_up() const;
    int get_down() const;
    Fraction negative() const;

private:
    int up, down;
    void simplify();

    friend void output(const Fraction &f);
    friend Fraction add(const Fraction &a, const Fraction &b);
    friend Fraction sub(const Fraction &a, const Fraction &b);
    friend Fraction mul(const Fraction &a, const Fraction &b);
    friend Fraction div(const Fraction &a, const Fraction &b);
};
