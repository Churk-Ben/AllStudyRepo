#pragma once

#include <iostream>
#include <string>

// 联系人类
class Contact {
public:
    Contact(const std::string &name_, const std::string &phone_);

    const std::string &get_name() const;
    const std::string &get_phone() const;
    void display() const;

private:
   std::string name;    // 必填项
   std::string phone;   // 必填项
};

Contact::Contact(const std::string &name_, const std::string &phone_):name{name_}, phone{phone_} {
}

const std::string& Contact::get_name() const {
    return name;
}

const std::string& Contact::get_phone() const {
    return phone;
}

void Contact::display() const {
    std::cout << "Name: " << name << ", Phone: " << phone << "\n";
}