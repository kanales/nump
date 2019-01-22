#include "Matrix.hpp"
#include <vector>
#include <utility>
#include <sstream>
#include <initializer_list>
#include <math.h>

using namespace npr;

Matrix::Matrix()
    : data(std::make_shared<std::vector<double>>())
{
    this->cols = 0;
    this->rows = 0;
    this->trans = false;
}

Matrix::Matrix(size_t rows, size_t cols)
    : data(std::make_shared<std::vector<double>>())
{
    this->data->resize(cols * rows);
    this->cols = cols;
    this->rows = rows;
    this->trans = false;
}

Matrix::Matrix(size_t rows, size_t cols, std::vector<double> &other_data)
    : data(new std::vector(other_data))
{
    assert(data->size() == cols * rows);
    this->cols = cols;
    this->rows = rows;
    this->trans = false;
}

Matrix::Matrix(Matrix &other)
    : data(std::make_shared<std::vector<double>>())
{
    std::copy(
        other.data->begin(),
        other.data->end(),
        this->data->begin());
    this->rows = other.rows;
    this->cols = other.cols;
    this->trans = false;
}
Matrix::Matrix(Matrix &&other)
    : data(std::make_shared<std::vector<double>>())
{
    std::swap(this->data, other.data);
    this->rows = other.rows;
    this->cols = other.cols;
    this->trans = false;
}

Matrix &Matrix::operator=(Matrix &other)
{
    return *this = Matrix(other);
}
Matrix &Matrix::operator=(Matrix &&other)
{
    return *this = Matrix(other);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) 
    : Matrix(lst.size(), lst.size() ? lst.begin()->size() : 0)
{
    this->rows = lst.size();
    this->cols = lst.begin()->size();
    int i = 0, j = 0;
    for (const auto &l : lst)
    {
        for (const auto &v : l)
        {
            (*this->data)[i + j * this->rows] = v;
            ++j;
        }
        j = 0;
        ++i;
    }
}

Matrix Matrix::reshape(size_t rows, size_t cols) const
{
    assert(cols * rows == this->cols * this->rows);
    Matrix m;
    m.data = this->data;
    m.cols = cols;
    m.rows = rows;
    return m;
}

double Matrix::sum() const 
{
    double acc = 0;
    for (auto it = this->data->begin();
         it != this->data->end(); it++)
    {
        acc += *it;
    }

    return acc;
}

Matrix Matrix::t() const
{
    Matrix out(this->cols, this->rows, *this->data);
    out.trans = true;
    return out;
}

double &Matrix::operator()(size_t i, size_t j)
{
    if (trans) std::swap(i,j);
    return (*this->data)[i + this->rows * j];
}

const double &Matrix::operator()(size_t i, size_t j) const
{
    if (trans) std::swap(i,j);
    return (*this->data)[i + this->rows * j];
}

Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix out(this->rows, this->cols);
    auto it2 = other.data->begin();
    auto it1 = this->data->begin();
    auto itout = out.data->begin();

    while (it2 != this->data->end())
    {
        *itout = *it1 + *it2;
        it1++;
        it2++;
        itout++;
    }
    return out;
}

Matrix Matrix::operator- (const Matrix &other) const
{
    Matrix out(this->rows, this->cols);
    auto it2 = other.data->begin();
    auto it1 = this->data->begin();
    auto itout = out.data->begin();

    while (it2 != this->data->end())
    {
        *itout = *it1 - *it2;
        it1++;
        it2++;
        itout++;
    }
    return out;
}
#include <iostream>
bool Matrix::operator==(const Matrix &other) const
{
    if (other.rows != this->rows || other.cols != this->cols)
        return false;
    // Frobenius norm
    double acc = 0;
    auto it1 = this->data->begin();
    auto it2 = other.data->begin();
    while (it1 != this->data->end())
    {
        double diff = *it1 - *it2;
        acc += diff * diff;
        it1++;it2++;
    }
    return sqrt(acc) < MATRIX_EPSILON;
}

Matrix Matrix::product(const Matrix &other) const
{
    Matrix out(this->rows, this->cols);
    auto it2 = other.data->begin();
    auto it1 = this->data->begin();
    auto itout = out.data->begin();
    while (it2 != this->data->end())
    {
        *itout = *it1 * *it2;
        it1++;
        it2++;
        itout++;
    }
    return out;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    assert(this->cols == other.rows);
    size_t n = this->rows,
           m = other.cols;
    Matrix out(n, m);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            int acc = 0;
            for (size_t k = 0; k < other.cols; k++)
            {
                acc += (*this)(i, k) * other(k, j);
            }
            out(i, j) = acc;
        }
    }

    return out;
}

std::string Matrix::str() const
{
    std::stringstream ss;
    std::string c = "{{";

    for (size_t i = 0; i < this->rows; i++)
    {
        ss << c; c = "\n {";
        ss << (*this)(i, 0);
        for (size_t j = 1; j < this->cols; j++)
        {
            ss << ", " << (*this)(i, j);
        }
        ss << '}';
    }
    ss << '}' << std::endl;

    return ss.str();
}

std::ostream &operator<<(std::ostream &os, Matrix const &m)
{
    return os << m.str();
}