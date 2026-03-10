#pragma once
#include <iostream>

template <typename T>
class Complex {
public:
    Complex() = default;
    Complex(T r, T i) : real(r), imag(i) {}
    Complex(const Complex& rhs) : real(rhs.real), imag(rhs.imag) {}

    T get_real() const { return real; }
    T get_imag() const { return imag; }

    Complex& operator+=(const Complex& rhs) {
        real += rhs.real;
        imag += rhs.imag;
        return *this;
    }

    friend Complex operator+(Complex lhs, const Complex& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend bool operator==(const Complex& a, const Complex& b) {
        return a.real == b.real && a.imag == b.imag;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << '+';
        os << c.imag << 'i';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        return is >> c.real >> c.imag;
    }

private:
    T real{};
    T imag{};
};
