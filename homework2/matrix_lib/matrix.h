#pragma once

#include <iostream>
#include "vector.h"

class HorizontalVector;
class VerticalVector;

class Matrix
{
public:
    Matrix() : rows(0), cols(0), data(0) {}
    Matrix(size_t n, size_t m);
    Matrix(double *arr, size_t n, size_t m);
    Matrix(HorizontalVector *arr, size_t size);
    Matrix(VerticalVector *arr, size_t size);
    Matrix(const Matrix &matrix);
    ~Matrix();

    Matrix &operator=(const Matrix &matrix);
    double operator()(size_t i, size_t j) const;
    double &operator()(size_t i, size_t j);
    bool operator==(const Matrix &matrix) const;
    bool operator!=(const Matrix &matrix) const;
    Matrix operator+(const Matrix &matrix) const;
    Matrix operator+(const double &value) const;
    Matrix operator+(const HorizontalVector &hVector) const;
    Matrix operator+(const VerticalVector &vVector) const;
    Matrix operator-(const Matrix &matrix) const;
    Matrix operator-(const double &value) const;
    Matrix operator-(const HorizontalVector &hVector) const;
    Matrix operator-(const VerticalVector &vVector) const;
    Matrix operator*(const Matrix &matrix) const;
    Matrix operator*(const double &value) const;
    Matrix operator*(const VerticalVector &vVector) const;
    Matrix operator*(const HorizontalVector &hVector) const;
    void operator+=(const Matrix &matrix);
    void operator+=(const double value);
    void operator-=(const Matrix &matrix);
    void operator-=(const double value);
    void operator*=(const double value);

    size_t getRows() const;
    size_t getCols() const;

    Matrix transp() const;
    double det() const;
    Matrix inv() const;

private:
    size_t rows;
    size_t cols;
    double *data;

    void calcDet(const Matrix &matrix, double *val) const;
    Matrix delColRow(size_t row, size_t col) const;
    Matrix adj() const;
};

Matrix operator+(double value, const Matrix &matrix);
Matrix operator*(double value, const Matrix &matrix);
Matrix operator*(const VerticalVector &vVector, const Matrix &matrix);
Matrix operator*(const HorizontalVector &hVector, const Matrix &matrix);
