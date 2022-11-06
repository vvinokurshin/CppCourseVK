#include <gtest/gtest.h>

#include "matrix.h"

TEST(Matrix, TestConstructorsDefault) {
    Matrix mat;

    EXPECT_EQ(mat.getRows(), 0);
    EXPECT_EQ(mat.getCols(), 0);
}

TEST(Matrix, TestConstructorsSizes) {
    size_t rows = 5, cols = 5;
    Matrix mat(rows, cols);

    EXPECT_EQ(mat.getRows(), rows);
    EXPECT_EQ(mat.getCols(), cols);
}

TEST(Matrix, TestConstructorsArray) {
    double arr[] = {1, 2, 3, 4, 5};
    Matrix mat(arr, 1, 5);

    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j)
            EXPECT_EQ(mat(i, j), arr[j]);
    }
}

TEST(Matrix, TestConstructorsHVector) {
    double arr[] = {1, 2, 3, 4, 5};
    HorizontalVector vec1(arr, 5), vec2(arr, 5);
    HorizontalVector VecArr[] = {vec1, vec2};
    Matrix mat(VecArr, 2);

    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j)
            EXPECT_EQ(mat(i, j), arr[j]);
    }
}

TEST(Matrix, TestConstructorsVVector) {
    double arr[] = {1, 2, 3, 4, 5};
    VerticalVector vec1(arr, 5), vec2(arr, 5);
    VerticalVector VecArr[] = {vec1, vec2};
    Matrix mat(VecArr, 2);

    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j)
            EXPECT_EQ(mat(i, j), arr[i]);
    }
}

TEST(Matrix, TestOperatorEQ) {
    double arr[] = {1, 2, 3, 4};
    Matrix mat1(arr, 2, 2);
    Matrix mat2 = mat1;

    EXPECT_EQ(mat1, mat2);
}

TEST(Matrix, TestOperatorPlusMatrix) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1}, arr3[] = {5, 5, 5, 5};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2), mat3(arr3, 2, 2);
    Matrix res = mat1 + mat2;

    EXPECT_EQ(res, mat3);
}

TEST(Matrix, TestOperatorPlusNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 5, 6, 7};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);

    Matrix res = mat1 + 3;
    EXPECT_EQ(res, mat2);

    res = 3 + mat1;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorPlusHVector) {
    double arr1[] = {1, 2, 3, 4}, arr_vec[] = {1, 2}, arr2[] = {2, 4, 4, 6};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);
    HorizontalVector vec(arr_vec, 2);

    Matrix res = mat1 + vec;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorPlusVVector) {
    double arr1[] = {1, 2, 3, 4}, arr_vec[] = {1, 2}, arr2[] = {2, 3, 5, 6};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);
    VerticalVector vec(arr_vec, 2);

    Matrix res = mat1 + vec;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorMinusMatrix) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1},
           arr3[] = {-3, -1, 1, 3};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2), mat3(arr3, 2, 2);
    Matrix res = mat1 - mat2;

    EXPECT_EQ(res, mat3);
}

TEST(Matrix, TestOperatorMinusNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {-2, -1, 0, 1};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);

    Matrix res = mat1 - 3;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorMinusHVector) {
    double arr1[] = {1, 2, 3, 4}, arr_vec[] = {1, 2}, arr2[] = {0, 0, 2, 2};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);
    HorizontalVector vec(arr_vec, 2);

    Matrix res = mat1 - vec;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorMinusVVector) {
    double arr1[] = {1, 2, 3, 4}, arr_vec[] = {1, 2}, arr2[] = {0, 1, 1, 2};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);
    VerticalVector vec(arr_vec, 2);

    Matrix res = mat1 - vec;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorMulMatrix) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1},
           arr3[] = {8, 5, 20, 13};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2), mat3(arr3, 2, 2);
    Matrix res = mat1 * mat2;

    EXPECT_EQ(res, mat3);
}

TEST(Matrix, TestOperatorMulNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {5, 10, 15, 20};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);

    Matrix res = mat1 * 5;
    EXPECT_EQ(res, mat2);

    res = 5 * mat1;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorMulHVector) {
    double arr1[] = {1, 2, 3, 4}, arr_vec[] = {1, 2},
           arr2[] = {1, 2, 2, 4, 3, 6, 4, 8};
    Matrix mat1(arr1, 4, 1), mat2(arr2, 4, 2);
    HorizontalVector vec(arr_vec, 2);

    Matrix res = mat1 * vec;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorMulVVector) {
    double arr1[] = {1, 2}, arr_vec[] = {1, 3}, arr2[] = {7};
    Matrix mat1(arr1, 1, 2), mat2(arr2, 1, 1);
    VerticalVector vec(arr_vec, 2);

    Matrix res = mat1 * vec;
    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorTrans) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {1, 3, 2, 4};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);
    Matrix res = mat1.transp();

    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestOperatorDet) {
    double arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix mat1(arr1, 3, 3);
    double res = mat1.det();

    EXPECT_EQ(res, 0);
}

TEST(Matrix, TestOperatorInv) {
    double arr1[] = {1, 2, 4, 4}, arr2[] = {-1, 0.5, 1, -0.25};
    Matrix mat1(arr1, 2, 2), mat2(arr2, 2, 2);
    Matrix res = mat1.inv();

    EXPECT_EQ(res, mat2);
}

TEST(Matrix, TestGetDiagonalSquare) {
    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, arr_vec[] = {1, 5, 9};
    Matrix mat(arr, 3, 3);
    HorizontalVector vec(arr_vec, 3);
    HorizontalVector res = mat.getDiagonal();

    EXPECT_EQ(res, vec);
}

TEST(Matrix, TestGetDiagonalRowsGtCols) {
    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, arr_vec[] = {1, 4};
    Matrix mat(arr, 5, 2);
    HorizontalVector vec(arr_vec, 2);
    HorizontalVector res = mat.getDiagonal();

    EXPECT_EQ(res, vec);
}

TEST(Matrix, TestGetDiagonalRowsLtCols) {
    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, arr_vec[] = {1, 7};
    Matrix mat(arr, 2, 5);
    HorizontalVector vec(arr_vec, 2);
    HorizontalVector res = mat.getDiagonal();

    EXPECT_EQ(res, vec);
}

TEST(Matrix, TestGetRow) {
    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, arr_vec[] = {4, 5, 6};
    Matrix mat(arr, 3, 3);
    HorizontalVector vec(arr_vec, 3);
    HorizontalVector res = mat.getRow(1);

    EXPECT_EQ(res, vec);
}

TEST(Matrix, TestGetCol) {
    double arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, arr_vec[] = {1, 4, 7};
    Matrix mat(arr1, 3, 3);
    VerticalVector vec(arr_vec, 3);
    VerticalVector res = mat.getCol(0);

    EXPECT_EQ(res, vec);
}
