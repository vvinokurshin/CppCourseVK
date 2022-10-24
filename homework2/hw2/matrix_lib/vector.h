#pragma once

#include <iostream>
#include "matrix.h"

class Matrix;

class Vector
{
public:
    Vector() : size(0), data(0) {}
    Vector(size_t n);
    Vector(double *arr, size_t n);
    Vector(const Vector &vector);
    virtual ~Vector() = 0;

    Vector &operator=(const Vector &vector);
    double operator[](size_t i) const;
    double &operator[](size_t i);
    bool operator==(const Vector &vector) const;
    bool operator!=(const Vector &vector) const;
    void operator+=(const Vector& vector);
    void operator+=(const double value);
    void operator-=(const Vector& vector);
    void operator-=(const double value);
    void operator*=(const double value);

    double getSize() const;

protected:
    size_t size;
    double *data;
};

class VerticalVector;

class HorizontalVector : public Vector
{
public:
    HorizontalVector() : Vector() {}
    HorizontalVector(size_t n): Vector(n) {}
    HorizontalVector(double *arr, size_t n): Vector(arr, n) {}
    HorizontalVector(const HorizontalVector &hVector): Vector(hVector) {}
    ~HorizontalVector() override;

    HorizontalVector operator+(const HorizontalVector& hVector) const;
    HorizontalVector operator+(const double &value) const;
    HorizontalVector operator-(const HorizontalVector& hVector) const;
    HorizontalVector operator-(const double &value) const;
    HorizontalVector operator*(const double &value) const;
    Matrix operator*(const VerticalVector& vVector) const;
};

HorizontalVector operator+(const double value, const HorizontalVector &hVector);
HorizontalVector operator*(const double value, const HorizontalVector &hVector);


class VerticalVector : public Vector
{
public:
    VerticalVector() : Vector() {}
    VerticalVector(size_t n): Vector(n) {}
    VerticalVector(double *arr, size_t n): Vector(arr, n) {}
    VerticalVector(const VerticalVector &vVector): Vector(vVector) {}
    ~VerticalVector() override;

    VerticalVector operator+(const VerticalVector& vVector) const;
    VerticalVector operator+(const double &value) const;
    VerticalVector operator-(const VerticalVector& vVector) const;
    VerticalVector operator-(const double &value) const;
    VerticalVector operator*(const double &value) const;
    Matrix operator*(const HorizontalVector& hVector) const;
};

VerticalVector operator+(const double value, const VerticalVector &vVector);
VerticalVector operator*(const double value, const VerticalVector &vVector);