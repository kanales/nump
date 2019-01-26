#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "solve.hpp"

TEST(foo, matrixConstruction) {
    int cols = 3;
    int rows = 4;

    npr::Matrix m
    {{10, 11, 12},
     {20, 21, 22},
     {30, 31, 32},
     {40, 41, 42}};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            EXPECT_EQ((i+1)*10 + j, m(i,j));
        }
    }
}

TEST(foo, matrixAddition) {
    int cols = 3;
    int rows = 4;

    npr::Matrix A
    {{10, 10, 10},
     {20, 20, 20},
     {30, 30, 30},
     {40, 40, 40}};

    npr::Matrix B
    {{1, 2, 3},
     {1, 2, 3},
     {1, 2, 3},
     {1, 2, 3}};

    npr::Matrix C = A + B;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            EXPECT_EQ((i+1)*10 + j, C(i,j));
        }
    }
}

TEST(foo, luFactorization) {
    npr::Matrix A 
    {{1,1,1},
     {1,2,2},
     {1,2,3}};
    auto [L, U] = npr::lu(A);
    EXPECT_EQ(A, L*U);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}