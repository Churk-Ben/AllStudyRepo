#pragma once

#include <array>
#include <string>
#include <vector>

class GradeCalc : private std::vector<int>
{
public:
    GradeCalc(const std::string &cname);
    void input(int n);                 // 录入n个成绩
    void output() const;               // 输出成绩
    void sort(bool ascending = false); // 排序 (默认降序)
    int min() const;                   // 返回最低分
    int max() const;                   // 返回最高分
    double average() const;            // 返回平均分
    void info();                       // 输出成绩统计信息

private:
    void compute(); // 计算成绩统计信息

private:
    std::string course_name;     // 课程名
    std::array<int, 5> counts;   // 保存各分数段人数（[0, 60), [60, 70), [70, 80), [80, 90), [90, 100]
    std::array<double, 5> rates; // 保存各分数段占比
    bool is_dirty;               // 脏标记，记录是否成绩信息有变更
};