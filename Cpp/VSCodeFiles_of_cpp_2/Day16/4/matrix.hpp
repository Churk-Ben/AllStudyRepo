#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>

// 类Matrix声明
class Matrix {
public:
    Matrix(int rows_, int cols_, double value = 0); // 构造rows_*cols_矩阵对象, 初值value
    Matrix(int rows_, double value = 0);    // 构造rows_*rows_方阵对象, 初值value
    Matrix(const Matrix &x);    // 深复制
    ~Matrix();

    void set(const double *pvalue, int size);   // 按行复制pvalue指向的数据，要求size=rows*cols,否则报错退出
    void clear();   // 矩阵对象数据项置0
    
    const double& at(int i, int j) const;   // 返回矩阵对象索引(i,j)对应的数据项const引用（越界则报错后退出）
    double& at(int i, int j);   // 返回矩阵对象索引(i,j)对应的数据项引用（越界则报错后退出）
    
    int rows() const;   // 返回矩阵对象行数
    int cols() const;   // 返回矩阵对象列数

    void print() const;   // 按行打印数据

private:
    int n_rows;      // 矩阵对象内元素行数
    int n_cols;       // 矩阵对象内元素列数
    double *ptr;    // 数据区
};