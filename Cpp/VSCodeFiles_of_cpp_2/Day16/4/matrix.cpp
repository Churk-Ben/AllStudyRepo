#include "matrix.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Matrix::Matrix(int rows_, int cols_, double value) : n_rows{rows_}, n_cols{cols_}, ptr{nullptr}
{
    if (n_rows <= 0 || n_cols <= 0)
    {
        std::cerr << "SizeError: rows and cols must be positive\n";
        std::exit(1);
    }
    ptr = new double[n_rows * n_cols];
    std::fill_n(ptr, n_rows * n_cols, value);
}

Matrix::Matrix(int rows_, double value) : Matrix(rows_, rows_, value)
{
}

Matrix::Matrix(const Matrix &x) : n_rows{x.n_rows}, n_cols{x.n_cols}, ptr{new double[n_rows * n_cols]}
{
    std::copy_n(x.ptr, n_rows * n_cols, ptr);
}

Matrix::~Matrix()
{
    delete[] ptr;
}

void Matrix::set(const double *pvalue, int size)
{
    if (size != n_rows * n_cols)
    {
        std::cerr << "SizeError: size mismatch\n";
        std::exit(1);
    }
    for (int i = 0; i < n_rows * n_cols; ++i)
        ptr[i] = pvalue[i];
}

void Matrix::clear()
{
    std::fill_n(ptr, n_rows * n_cols, 0);
}

const double &Matrix::at(int i, int j) const
{
    if (i < 0 || i >= n_rows || j < 0 || j >= n_cols)
    {
        std::cerr << "IndexError: index out of range\n";
        std::exit(1);
    }
    return ptr[i * n_cols + j];
}

double &Matrix::at(int i, int j)
{
    if (i < 0 || i >= n_rows || j < 0 || j >= n_cols)
    {
        std::cerr << "IndexError: index out of range\n";
        std::exit(1);
    }
    return ptr[i * n_cols + j];
}

int Matrix::rows() const
{
    return n_rows;
}

int Matrix::cols() const
{
    return n_cols;
}

void Matrix::print() const
{
    for (int i = 0; i < n_rows; ++i)
    {
        std::cout << at(i, 0);
        for (int j = 1; j < n_cols; ++j)
            std::cout << ", " << at(i, j);
        std::cout << '\n';
    }
}