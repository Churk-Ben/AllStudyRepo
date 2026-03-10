#include "stumgr.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

void StuMgr::load(const std::string &file)
{
    std::ifstream ifs(file);
    if (!ifs)
        throw std::runtime_error("cannot open file: " + file);

    std::string line;
    std::getline(ifs, line); // 跳过表头

    students.clear();
    Student tmp;
    while (ifs >> tmp)
        students.push_back(tmp);
}

void StuMgr::sort()
{
    std::stable_sort(students.begin(), students.end(),
                     [](const Student &a, const Student &b)
                     {
                         if (a.get_major() != b.get_major())
                             return a.get_major() < b.get_major();
                         return a.get_grade() > b.get_grade();
                     });
}

void StuMgr::write(std::ostream &os) const
{
    for (const auto &s : students)
        os << s << '\n';
}

void StuMgr::print() const
{
    write(std::cout);
}

void StuMgr::save(const std::string &file) const
{
    std::ofstream ofs(file);
    if (!ofs)
        throw std::runtime_error("cannot open file: " + file);
    write(ofs);
}
