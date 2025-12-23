#pragma once
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "contestant.hpp"

// ACM 排序规则：先按解题数降序，再按罚时升序
inline bool cmp_by_solve(const Contestant& a, const Contestant& b) {
    if(a.solved != b.solved)
        return a.solved > b.solved;
    
    return a.penalty < b.penalty;
}

// 将结果写至任意输出流
inline void write(std::ostream& os, const std::vector<Contestant>& v) {
    for (const auto& x : v) 
        os << x << '\n';
}

// 将结果打印到屏幕
inline void print(const std::vector<Contestant>& v) {
    write(std::cout, v);
}

// 将结果保存到文件
inline void save(const std::string& filename, const std::vector<Contestant>& v) {
    std::ofstream os(filename);
    if (!os) 
        throw std::runtime_error("fail to open " + filename);

    write(os, v);
}

// 从文件读取信息（跳过标题行）
inline std::vector<Contestant> load(const std::string& filename) {
    std::ifstream is(filename);
    if (!is) 
        throw std::runtime_error("fail to open " + filename);

    std::string line;
    std::getline(is, line);          // 跳过标题

    std::vector<Contestant> v;
    Contestant t;
    int seq;
    while (is >> seq >> t) 
        v.push_back(t);
        
    return v;
}