#include "student.hpp"
#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Student &s)
{
    os << std::left
       << std::setw(10) << s.id
       << std::setw(10) << s.name
       << std::setw(10) << s.major
       << std::setw(5) << s.grade;
    return os;
}

std::istream &operator>>(std::istream &is, Student &s)
{
    is >> s.id >> s.name >> s.major >> s.grade;
    return is;
}
