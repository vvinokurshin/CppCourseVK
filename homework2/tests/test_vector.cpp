#include <gtest/gtest.h>

#include "vector.h"

TEST(hVector, TestConstructorsDefault) {
    HorizontalVector vec;

    EXPECT_EQ(vec.getSize(), 0);
}

TEST(hVector, TestConstructorsSize) {
    size_t size = 5;
    HorizontalVector vec(size);

    EXPECT_EQ(vec.getSize(), size);
}

TEST(hVector, TestConstructorsArray) {
    double arr[] = {1, 2, 3, 4, 5};
    HorizontalVector vec(arr, 5);

    for (size_t i = 0; i < vec.getSize(); ++i)
        EXPECT_EQ(vec[i], arr[i]);
}

TEST(hVector, TestOperatorEQ) {
    double arr[] = {1, 2, 3, 4};
    HorizontalVector vec1(arr, 4);
    HorizontalVector vec2 = vec1;

    EXPECT_EQ(vec1, vec2);
}

TEST(hVector, TestOperatorPlusVector) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1}, arr3[] = {5, 5, 5, 5};
    HorizontalVector vec1(arr1, 4), vec2(arr2, 4), vec3(arr3, 4);
    HorizontalVector res = vec1 + vec2;

    EXPECT_EQ(res, vec3);
}

TEST(hVector, TestOperatorPlusNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {3, 4, 5, 6};
    HorizontalVector vec1(arr1, 4), vec2(arr2, 4);
    HorizontalVector res = vec1 + 2;

    EXPECT_EQ(res, vec2);
}

TEST(hVector, TestOperatorMinusVector) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1},
           arr3[] = {-3, -1, 1, 3};
    HorizontalVector vec1(arr1, 4), vec2(arr2, 4), vec3(arr3, 4);
    HorizontalVector res = vec1 - vec2;

    EXPECT_EQ(res, vec3);
}

TEST(hVector, TestOperatorMinusNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {-1, 0, 1, 2};
    HorizontalVector vec1(arr1, 4), vec2(arr2, 4);
    HorizontalVector res = vec1 - 2;

    EXPECT_EQ(res, vec2);
}

TEST(hVector, TestOperatorMulNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {2, 4, 6, 8};
    HorizontalVector vec1(arr1, 4), vec2(arr2, 4);
    HorizontalVector res = vec1 * 2;

    EXPECT_EQ(res, vec2);
}

TEST(hVector, TestOperatorMulVector) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {1, 2, 3, 4}, arr3[] = {30};
    HorizontalVector vec1(arr1, 4);
    VerticalVector vec2(arr2, 4);
    Matrix mat(arr3, 1, 1), res = vec1 * vec2;

    EXPECT_EQ(res, mat);
}

TEST(hVector, TestSliceNormal) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {2, 3, 4, 5};
    HorizontalVector vec1(arr1, 10), vec2(arr2, 4);
    HorizontalVector res = vec1.slice(2, 6);

    EXPECT_EQ(res, vec2);
}

TEST(hVector, TestSliceOneElement) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {0};
    HorizontalVector vec1(arr1, 10), vec2(arr2, 1);
    HorizontalVector res = vec1.slice(0, 1);

    EXPECT_EQ(res, vec2);
}

TEST(hVector, TestLSlice) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {6, 7, 8, 9};
    HorizontalVector vec1(arr1, 10), vec2(arr2, 4);
    HorizontalVector res = vec1.lslice(6);

    EXPECT_EQ(res, vec2);
}

TEST(hVector, TestRSlice) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {0, 1, 2, 3, 4, 5};
    HorizontalVector vec1(arr1, 10), vec2(arr2, 6);
    HorizontalVector res = vec1.rslice(6);

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestConstructorsDefault) {
    VerticalVector vec;

    EXPECT_EQ(vec.getSize(), 0);
}

TEST(vVector, TestConstructorsSize) {
    size_t size = 5;
    VerticalVector vec(size);

    EXPECT_EQ(vec.getSize(), size);
}

TEST(vVector, TestConstructorsArray) {
    double arr[] = {1, 2, 3, 4, 5};
    VerticalVector vec(arr, 5);

    for (size_t i = 0; i < vec.getSize(); ++i)
        EXPECT_EQ(vec[i], arr[i]);
}

TEST(vVector, TestOperatorEQ) {
    double arr[] = {1, 2, 3, 4};
    VerticalVector vec1(arr, 4);
    VerticalVector vec2 = vec1;

    EXPECT_EQ(vec1, vec2);
}

TEST(vVector, TestOperatorPlusVector) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1}, arr3[] = {5, 5, 5, 5};
    VerticalVector vec1(arr1, 4), vec2(arr2, 4), vec3(arr3, 4);
    VerticalVector res = vec1 + vec2;

    EXPECT_EQ(res, vec3);
}

TEST(vVector, TestOperatorMinusVector) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {4, 3, 2, 1},
           arr3[] = {-3, -1, 1, 3};
    VerticalVector vec1(arr1, 4), vec2(arr2, 4), vec3(arr3, 4);
    VerticalVector res = vec1 - vec2;

    EXPECT_EQ(res, vec3);
}

TEST(vVector, TestOperatorPlusNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {3, 4, 5, 6};
    VerticalVector vec1(arr1, 4), vec2(arr2, 4);
    VerticalVector res = vec1 + 2;

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestOperatorMinusNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {-1, 0, 1, 2};
    VerticalVector vec1(arr1, 4), vec2(arr2, 4);
    VerticalVector res = vec1 - 2;

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestOperatorMulNum) {
    double arr1[] = {1, 2, 3, 4}, arr2[] = {2, 4, 6, 8};
    VerticalVector vec1(arr1, 4), vec2(arr2, 4);
    VerticalVector res = vec1 * 2;

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestOperatorMulVector) {
    double arr1[] = {1, 2}, arr2[] = {1, 2}, arr3[] = {1, 2, 2, 4};
    VerticalVector vec1(arr1, 2);
    HorizontalVector vec2(arr2, 2);
    Matrix mat(arr3, 2, 2), res = vec1 * vec2;

    EXPECT_EQ(res, mat);
}

TEST(vVector, TestSliceNormal) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {2, 3, 4, 5};
    VerticalVector vec1(arr1, 10), vec2(arr2, 4);
    VerticalVector res = vec1.slice(2, 6);

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestSliceOneElement) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {0};
    VerticalVector vec1(arr1, 10), vec2(arr2, 1);
    VerticalVector res = vec1.slice(0, 1);

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestLSlice) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {6, 7, 8, 9};
    VerticalVector vec1(arr1, 10), vec2(arr2, 4);
    VerticalVector res = vec1.lslice(6);

    EXPECT_EQ(res, vec2);
}

TEST(vVector, TestRSlice) {
    double arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, arr2[] = {0, 1, 2, 3, 4, 5};
    VerticalVector vec1(arr1, 10), vec2(arr2, 6);
    VerticalVector res = vec1.rslice(6);

    EXPECT_EQ(res, vec2);
}
