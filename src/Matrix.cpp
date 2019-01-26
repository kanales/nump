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
    this->_cols = 0;
    this->_rows = 0;
    this->trans = false;
}

Matrix::Matrix(size_t rows, size_t cols)
    : data(std::make_shared<std::vector<double>>())
{
    this->data->resize(cols * rows);
    this->_cols = cols;
    this->_rows = rows;
    this->trans = false;
}

Matrix::Matrix(size_t rows, size_t cols, std::vector<double> &other_data)
    : data(new std::vector<double>(other_data))
{
    this->_cols = cols;
    this->_rows = rows;
    this->trans = false;
}
#include <iostream>
Matrix::Matrix(const Matrix &other)
    : data(std::make_shared<std::vector<double>>())
{
    std::copy(
        other.data->begin(),
        other.data->end(),
        std::back_inserter(*this->data));
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->trans = false;
}
Matrix::Matrix(Matrix &&other)
    : data(std::make_shared<std::vector<double>>())
{
    std::swap(this->data, other.data);
    this->_rows = other._rows;
    this->_cols = other._cols;
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
    this->_rows = lst.size();
    this->_cols = lst.begin()->size();
    int i = 0, j = 0;
    for (const auto &l : lst)
    {
        for (const auto &v : l)
        {
            (*this->data)[i + j * this->_rows] = v;
            ++j;
        }
        j = 0;
        ++i;
    }
}

Matrix Matrix::reshape(size_t rows, size_t cols) const
{
    Matrix m;
    m.data = this->data;
    m._cols = cols;
    m._rows = rows;
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
    Matrix out(this->_cols, this->_rows, *this->data);
    out.trans = true;
    return out;
}

double &Matrix::operator()(size_t i, size_t j)
{
    if (trans)
        std::swap(i, j);
    return (*this->data)[i + this->_rows * (j-1) - 1];
}

double &Matrix::operator ()(size_t k) {
    return (*this->data)[k - 1];
}

const double &Matrix::operator()(size_t i, size_t j) const
{
    if (trans)
        std::swap(i, j);
    return (*this->data)[i + this->_rows * (j-1) - 1];
}

const double &Matrix::operator()(size_t k) const
{
    return (*this->data)[k - 1];
}

Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix out(this->_rows, this->_cols);
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

Matrix Matrix::operator-(const Matrix &other) const
{
    Matrix out(this->_rows, this->_cols);
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
    if (other._rows != this->_rows || other._cols != this->_cols)
        return false;
    // Frobenius norm
    double acc = 0;
    auto it1 = this->data->begin();
    auto it2 = other.data->begin();
    while (it1 != this->data->end())
    {
        double diff = *it1 - *it2;
        acc += diff * diff;
        it1++;
        it2++;
    }
    return sqrt(acc) < MATRIX_EPSILON;
}

Matrix Matrix::product(const Matrix &other) const
{
    Matrix out(this->_rows, this->_cols);
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
    size_t n = this->_rows,
           m = other._cols;
    Matrix out(n, m);

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            int acc = 0;
            for (size_t k = 1; k <= other._cols; k++)
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

    for (size_t i = 1; i <= this->_rows; i++)
    {
        ss << c;
        c = ",\n {";
        ss << (*this)(i, 1);
        for (size_t j = 2; j <= this->_cols; j++)
        {
            ss << ", " << (*this)(i, j);
        }
        ss << '}';
    }
    ss << '}' << std::endl;

    return ss.str();
}

size_t Matrix::rows() const
{
    return this->_rows;
}

size_t Matrix::cols() const
{
    return this->_cols;
}

Matrix zeros(size_t rows, size_t cols)
{
    Matrix m(rows, cols);

    for (int i = 1; i <= m.cols(); i++)
    {
        for (int j = 1; i <= m.rows(); j++)
        {
            m(i,j) = 0;
        }
    }

    return m;
}

Matrix ones(size_t rows, size_t cols)
{
    Matrix m(rows, cols);

    for (int i = 1; i <= m.cols(); i++)
    {
        for (int j = 1; i <= m.rows(); j++)
        {
            m(i,j) = 1;
        }
    }

    return m;
}

std::ostream &operator<<(std::ostream &os, Matrix const &m)
{
    return os << m.str();
}