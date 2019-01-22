#ifndef MATRIX_HPP
#define MATRIX_HPP

#ifndef MATRIX_EPSILON
#define MATRIX_EPSILON std::numeric_limits<double>::epsilon()
#endif

#include <vector>
namespace npr {

class Matrix
{
  private:
    std::shared_ptr<std::vector<double>> data;
    size_t rows;
    size_t cols;
    bool trans;
  public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, std::vector<double> &data);
    Matrix(Matrix &other);
    Matrix(Matrix &&other);
    Matrix &operator=(Matrix &other);
    Matrix &operator=(Matrix &&other);
    Matrix(std::initializer_list<std::initializer_list<double>> lst);

    Matrix reshape(size_t rows, size_t cols) const;
    Matrix product(const Matrix &other) const;
    double sum() const;
    Matrix t() const;

    Matrix operator+ (const Matrix &other) const;
    Matrix operator* (const Matrix &other) const;
    Matrix operator- (const Matrix &other) const;
    bool   operator==(const Matrix &other) const;
    inline double &operator ()(size_t i, size_t j);
    inline const double &operator()(size_t i, size_t j) const;
    

    std::string str() const;
};

}

std::ostream &operator<<(std::ostream &os, npr::Matrix const &m);

#endif