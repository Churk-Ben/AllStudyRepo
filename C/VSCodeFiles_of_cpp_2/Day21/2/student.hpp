#pragma once

#include <iostream>
#include <string>

class Student {
public:
    Student() = default;
    ~Student() = default;
    
    const std::string& get_major() const { return major; }
    int get_grade() const { return grade; }

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);

private:
    int id;   
    std::string  name;
    std::string  major;
    int          grade;  // 0-100
};
