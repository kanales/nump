#include "solve.hpp"

#include <iostream>
// std::tuple<npr::Matrix,npr::Matrix> lu(npr::Matrix& m) {
//     Matrix L()
// }

npr::Matrix npr::gaussJordan(npr::Matrix A, npr::Matrix b) {
    // Assuming A in R(n,n); b in R(n,1)
    
    // Forward elimination
    int n = A.rows();
    double factor;
    for (int j = 1; j <= n-1; j++) {
        for (int i = j+1; i <= n; i++) {
            factor = A(i,j) / A(j,j);
            A(i,j) = 0;
            for (int k = j+1; k <= n; k++) {
                A(i,k) = A(i,k) - factor * A(j,k);
            }
            b(i) = b(i) - factor * b(j);
        }
    }
    npr::Matrix x(n,1);
    // Back substitution
    for (int i = n; i >= 1; i--) {
        double acc = 0;
        for (int j = i+1; j <= n; j++) {
            acc += A(i,j) * x(j);
        }
        x(i) = (b(i) - acc) / A(i,i);
    }

    return x;
}

std::tuple<npr::Matrix, npr::Matrix> npr::lu(npr::Matrix &A) {
    int n = A.cols();
    npr::Matrix L(n,n);
    npr::Matrix U(n,n);

    for (int i = 1; i <= n; i++) {
        L(i,i) = 1;
        for (int k = 1; k < i; k++) {
            double sum = 0; for (int j = 1; j < k; j++) sum += L(i,j) * U(j,k);
            L(i,k) = (A(i,k) - sum) / U(k,k);
        }

        for (int k = i; k <= n; k++) {
            double sum = 0; for (int j = 1; j < i; j++) sum += L(i,j) * U(j,k);
            U(i,k) = A(i,k) - sum;
        }
    }
    return {std::move(L), std::move(U)};
}