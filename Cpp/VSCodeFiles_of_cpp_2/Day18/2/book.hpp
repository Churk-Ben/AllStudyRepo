#pragma once
#include <string>

// 图书描述信息类Book: 声明
class Book {
public:
    Book(const std::string &name_, 
         const std::string &author_, 
         const std::string &translator_, 
         const std::string &isbn_, 
         double price_);

    friend std::ostream& operator<<(std::ostream &out, const Book &book);

private:
    std::string name;        // 书名
    std::string author;      // 作者
    std::string translator;  // 译者
    std::string isbn;        // isbn号
    double price;        // 定价
};