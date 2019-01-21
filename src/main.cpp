#include "Matrix.hpp"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    Matrix A {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Matrix B {
        {0,1,0},
        {1,0,0},
        {0,0,1}
    };

    Matrix C {
        {4,5,6},
        {1,2,3},
        {7,8,9}
    };
    std::cout << (B * A) << '\n' << C << ((B * A) == C);
    return 0;
}