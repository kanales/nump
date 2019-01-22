#include "Matrix.hpp"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    npr::Matrix A 
    {{1,2,3},
     {4,5,6},
     {7,8,9}};
    std::cout << A.t();
    return 0;
}