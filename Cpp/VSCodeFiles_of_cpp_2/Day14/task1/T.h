#pragma once

#include <string>

// 类T: 声明
class T
{
    // 对象属性、方法
public:
    T(int x = 0, int y = 0); // 普通构造函数
    T(const T &t);           // 复制构造函数
    T(T &&t);                // 移动构造函数
    ~T();                    // 析构函数

    void adjust(int ratio); // 按系数成倍调整数据
    void display() const;   // 以(m1, m2)形式显示T类对象信息

private:
    int m1, m2;

    // 类属性、方法
public:
    static int get_cnt(); // 显示当前T类对象总数

public:
    static const std::string doc; // 类T的描述信息
    static const int max_cnt;     // 类T对象上限

private:
    static int cnt; // 当前T类对象数目

    // 类T友元函数声明
    friend void func();
};

// 普通函数声明
void func();