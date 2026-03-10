#pragma once

#include <string>
#include <vector>

enum class GraphType
{
    circle,
    triangle,
    rectangle
};

// Graph类定义
class Graph
{
public:
    virtual void draw() {}
    virtual ~Graph() = default;
};

// Circle类声明
class Circle : public Graph
{
public:
    void draw();
};

// Triangle类声明
class Triangle : public Graph
{
public:
    void draw();
};

// Rectangle类声明
class Rectangle : public Graph
{
public:
    void draw();
};

// Canvas类声明
class Canvas
{
public:
    void add(const std::string &type); // 根据字符串添加图形
    void paint() const;                // 使用统一接口绘制所有图形
    ~Canvas();                         // 手动释放资源

private:
    std::vector<Graph *> graphs;
};

// 4. 工具函数
GraphType str_to_GraphType(const std::string &s); // 字符串转枚举类型
Graph *make_graph(const std::string &type);       // 创建图形，返回堆对象指针