#include "Complex.h"
#include <iostream>
#include <cmath>

const std::string Complex::doc{"a simplified Complex class"};

Complex::Complex() : real{0}, imag{0} {}
Complex::Complex(double r) : real{r}, imag{0} {}
Complex::Complex(double r, double i) : real{r}, imag{i} {}
Complex::Complex(const Complex &c) : real{c.real}, imag{c.imag} {}

double Complex::get_real() const { return real; }
double Complex::get_imag() const { return imag; }

void Complex::add(const Complex &c)
{
    real += c.real;
    imag += c.imag;
}

void output(const Complex &c)
{
    std::cout << c.real << (c.imag >= 0 ? " + " : " - ") << std::abs(c.imag) << "i";
}

double abs(const Complex &c)
{
    return std::sqrt(c.real * c.real + c.imag * c.imag);
}

Complex add(const Complex &a, const Complex &b)
{
    return Complex(a.real + b.real, a.imag + b.imag);
}

bool is_equal(const Complex &a, const Complex &b)
{
    return a.real == b.real && a.imag == b.imag;
}

bool is_not_equal(const Complex &a, const Complex &b)
{
    return !is_equal(a, b);
}
