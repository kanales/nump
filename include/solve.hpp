#ifndef SOLVE_HPP
#define SOLVE_HPP

#include "Matrix.hpp"
#include <tuple>

namespace npr
{
std::tuple<npr::Matrix,npr::Matrix> lu(npr::Matrix &A);
npr::Matrix gaussJordan(npr::Matrix A, npr::Matrix b);
} // npr

#endif