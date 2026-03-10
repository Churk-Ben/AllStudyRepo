#pragma once

#include <string>

// 发行/出版物类：Publisher （抽象类）
class Publisher {
public:
    Publisher(const std::string &name_ = "");            // 构造函数
    virtual ~Publisher() = default;

public:
    virtual void publish() const = 0;                 // 纯虚函数，作为接口继承
    virtual void use() const = 0;                     // 纯虚函数，作为接口继承

protected:
    std::string name;    // 发行/出版物名称
};

// 图书类: Book
class Book: public Publisher {
public:
    Book(const std::string &name_ = "", const std::string &author_ = "");  // 构造函数

public:
    void publish() const override;        // 接口
    void use() const override;            // 接口

private:
    std::string author;          // 作者
};

// 电影类: Film
class Film: public Publisher {
public:
    Film(const std::string &name_ = "", const std::string &director_ = "");   // 构造函数

public:
    void publish() const override;    // 接口
    void use() const override;        // 接口            

private:
    std::string director;        // 导演
};


// 音乐类：Music
class Music: public Publisher {
public:
    Music(const std::string &name_ = "", const std::string &artist_ = "");

public:
    void publish() const override;        // 接口
    void use() const override;            // 接口

private:
    std::string artist;      // 音乐艺术家名称
};