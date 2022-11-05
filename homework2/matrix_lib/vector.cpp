#include <cassert>
#include "vector.h"
#include <cmath>

Vector::~Vector() {}

Vector::Vector(size_t n) : size(n)
{
    data = new double[size];
}

Vector::Vector(double *arr, size_t n) : Vector(n)
{
    std::copy(arr, arr + n, data);
}

Vector::Vector(const Vector &vector) : Vector(vector.data, vector.size) {}

Vector &Vector::operator=(const Vector &vector)
{
    delete[] data;

    size = vector.size;
    data = new double[size];
    std::copy(vector.data, vector.data + size, data);

    return *this;
}

double Vector::operator[](size_t i) const
{
    assert(i < size);
    return data[i];
}

double &Vector::operator[](size_t i)
{
    assert(i < size);
    return data[i];
}

bool Vector::operator==(const Vector &vector) const
{
    if (size != vector.size)
    {
        return false;
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (fabs(data[i] - vector.data[i]) > 1e-7)
        {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector &vector) const
{
    return !((*this) == vector);
}

void Vector::operator+=(const Vector &vector)
{
    assert(size == vector.size);

    for (size_t i = 0; i < size; ++i)
    {
        data[i] += vector.data[i];
    }
}

void Vector::operator+=(const double value)
{
    for (size_t i = 0; i < size; ++i)
    {
        data[i] += value;
    }
}

void Vector::operator-=(const Vector &vector)
{
    assert(size == vector.size);

    for (size_t i = 0; i < size; ++i)
    {
        data[i] -= vector.data[i];
    }
}

void Vector::operator-=(const double value)
{
    for (size_t i = 0; i < size; ++i)
    {
        data[i] -= value;
    }
}

void Vector::operator*=(const double value)
{
    for (size_t i = 0; i < size; ++i)
    {
        data[i] *= value;
    }
}

double Vector::getSize() const
{
    return size;
}

HorizontalVector HorizontalVector::operator+(const HorizontalVector &hVector) const
{
    assert(size == hVector.size);

    HorizontalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] + hVector.data[i];
    }

    return result;
}

HorizontalVector HorizontalVector::operator+(const double &value) const
{
    HorizontalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] + value;
    }

    return result;
}

HorizontalVector HorizontalVector::operator-(const HorizontalVector &hVector) const
{
    assert(size == hVector.size);

    HorizontalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] - hVector.data[i];
    }

    return result;
}

HorizontalVector HorizontalVector::operator-(const double &value) const
{
    HorizontalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] - value;
    }

    return result;
}

HorizontalVector HorizontalVector::operator*(const double &value) const
{
    HorizontalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = value * data[i];
    }

    return result;
}

HorizontalVector::~HorizontalVector()
{
    delete[] data;
}

Matrix HorizontalVector::operator*(const VerticalVector &vVector) const
{
    assert(size == vVector.getSize());

    Matrix result(1, 1);
    result(0, 0) = 0;

    for (size_t i = 0; i < size; ++i)
    {
        result(0, 0) += data[i] * vVector[i];
    }

    return result;
}

HorizontalVector operator+(const double value, const HorizontalVector &hVector)
{
    return hVector + value;
}

HorizontalVector operator*(const double value, const HorizontalVector &hVector)
{
    return hVector * value;
}


VerticalVector VerticalVector::operator+(const VerticalVector &vVector) const
{
    assert(size == vVector.size);

    VerticalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] + vVector.data[i];
    }

    return result;
}

VerticalVector VerticalVector::operator+(const double &value) const
{
    VerticalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] + value;
    }

    return result;
}

VerticalVector VerticalVector::operator-(const VerticalVector &vVector) const
{
    assert(size == vVector.size);

    VerticalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] - vVector.data[i];
    }

    return result;
}

VerticalVector VerticalVector::operator-(const double &value) const
{
    VerticalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = data[i] - value;
    }

    return result;
}

VerticalVector VerticalVector::operator*(const double &value) const
{
    VerticalVector result(size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = value * data[i];
    }

    return result;
}

VerticalVector::~VerticalVector()
{
    delete[] data;
}

Matrix VerticalVector::operator*(const HorizontalVector &hVector) const
{
    Matrix result(size, hVector.getSize());
    result(0, 0) = 0;

    for (size_t i = 0; i < result.getRows(); ++i)
    {
        for (size_t j = 0; j < result.getRows(); ++j)
        {
            result(i, j) = (*this)[i] * hVector[j];
        }
    }

    return result;
}

VerticalVector operator+(const double value, const VerticalVector &vVector)
{
    return vVector + value;
}

VerticalVector operator*(const double value, const VerticalVector &vVector)
{
    return vVector * value;
}
