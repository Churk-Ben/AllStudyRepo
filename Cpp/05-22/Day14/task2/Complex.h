#pragma once
#include <string>

class Complex
{
public:
    static const std::string doc;

    Complex();
    Complex(double r);
    Complex(double r, double i);
    Complex(const Complex &c);

    double get_real() const;
    double get_imag() const;
    void add(const Complex &c);

    friend void output(const Complex &c);
    friend double abs(const Complex &c);
    friend Complex add(const Complex &a, const Complex &b);
    friend bool is_equal(const Complex &a, const Complex &b);
    friend bool is_not_equal(const Complex &a, const Complex &b);

private:
    double real, imag;
};
