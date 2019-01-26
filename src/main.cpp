#include "Matrix.hpp"
#include "solve.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    npr::Matrix A 
    {{1,1,1},
     {1,2,2},
     {1,2,3}};
    npr::Matrix b
    {{4},
     {6},
     {2}};

    npr::Matrix c(b);

    //std::cout << b(1);
    std::cout << "Result:" << std::endl;
    //std::cout << A;
    auto [L,U] = npr::lu(A);
    std::cout << L;
    std::cout << U;
    std::cout << L * U;
    std::cout << ((L * U) == A);
    return 0;
}