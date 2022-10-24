#include "matrix.h"
#include <cassert>
#include <cmath>

Matrix::Matrix(size_t n, size_t m) : rows(n), cols(m)
{
    data = new double[rows * cols];
}

Matrix::Matrix(double *arr, size_t n, size_t m) : Matrix(n, m)
{
    std::copy(arr, arr + n * m, data);
}

Matrix::Matrix(HorizontalVector *arr, size_t size)
{
    assert(arr != nullptr && size > 0);
    rows = size;
    cols = arr[0].getSize();

    for (size_t i = 1; i < size; ++i)
        assert(cols == arr[i].getSize());

    data = new double[rows * cols];

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            data[i * cols + j] = arr[i][j];
}

Matrix::Matrix(VerticalVector *arr, size_t size)
{
    assert(arr != nullptr && size > 0);
    rows = arr[0].getSize();
    cols = size;

    for (size_t i = 1; i < size; ++i)
        assert(rows == arr[i].getSize());

    data = new double[rows * cols];

    for (size_t i = 0; i < cols; ++i)
        for (size_t j = 0; j < rows; ++j)
            data[j * cols + i] = arr[i][j];
}

Matrix::Matrix(const Matrix &matrix) : Matrix(matrix.data, matrix.rows, matrix.cols) {}

Matrix::~Matrix()
{
    delete[] data;
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
    delete[] data;

    rows = matrix.rows;
    cols = matrix.cols;
    data = new double[rows * cols];

    std::copy(matrix.data, matrix.data + rows * cols, data);

    return *this;
}

double Matrix::operator()(size_t i, size_t j) const
{
    return data[i * cols + j];
}

double &Matrix::operator()(size_t i, size_t j)
{
    return data[i * cols + j];
}

bool Matrix::operator==(const Matrix &matrix) const
{
    if (rows != matrix.rows || cols != matrix.cols)
        return false;

    for (size_t i = 0; i < rows * cols; ++i)
        if (fabs(data[i] - matrix.data[i]) > 1e-7)
            return false;

    return true;
}

bool Matrix::operator!=(const Matrix &matrix) const
{
    return !((*this) == matrix);
}

Matrix Matrix::operator+(const Matrix &matrix) const
{
    assert(rows == matrix.rows && cols == matrix.cols);
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows * cols; ++i)
        result.data[i] = data[i] + matrix.data[i];

    return result;
}

Matrix Matrix::operator+(const double &value) const
{
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows * cols; ++i)
        result.data[i] = value + data[i];

    return result;
}

Matrix Matrix::operator+(const HorizontalVector &hVector) const
{
    assert(cols == hVector.getSize());
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result(i, j) = (*this)(i, j) + hVector[j];

    return result;            
}

Matrix Matrix::operator+(const VerticalVector &vVector) const
{
    assert(rows == vVector.getSize());
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result(i, j) = (*this)(i, j) + vVector[i];

    return result;            
}

Matrix Matrix::operator-(const Matrix &matrix) const
{
    assert(rows == matrix.rows && cols == matrix.cols);
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows * cols; ++i)
        result.data[i] = data[i] - matrix.data[i];

    return result;
}

Matrix Matrix::operator-(const HorizontalVector &hVector) const
{
    assert(cols == hVector.getSize());
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result(i, j) = (*this)(i, j) - hVector[j];

    return result;            
}

Matrix Matrix::operator-(const VerticalVector &vVector) const
{
    assert(rows == vVector.getSize());
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result(i, j) = (*this)(i, j) - vVector[i];

    return result;            
}

Matrix Matrix::operator-(const double &value) const
{
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows * cols; ++i)
        result.data[i] = data[i] - value;

    return result;
}

Matrix Matrix::operator*(const double &value) const
{
    Matrix result(rows, cols);

    for (size_t i = 0; i < rows * cols; ++i)
        result.data[i] = value * data[i];

    return result;
}

Matrix Matrix::operator*(const Matrix &matrix) const
{
    assert(cols == matrix.rows);
    Matrix result(rows, matrix.cols);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < matrix.cols; ++j)
        {
            result(i, j) = 0;

            for (size_t k = 0; k < cols; ++k)
                result(i, j) += (*this)(i, k) * matrix(k, j);
        }

    return result;
}

Matrix Matrix::operator*(const VerticalVector &vVector) const
{
    assert(cols == vVector.getSize());
    Matrix result(rows, 1);

    for (size_t i = 0; i < rows; ++i)
    {
        result(i, 0) = 0;

        for (size_t k = 0; k < cols; ++k)
            result(i, 0) += (*this)(i, k) * vVector[k];
    }

    return result;
}

Matrix Matrix::operator*(const HorizontalVector &hVector) const
{
    assert(cols == 1);
    Matrix result(rows, hVector.getSize());

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < hVector.getSize(); ++j)
            result(i, j) = (*this)(i, 0) * hVector[j];

    return result;
}

void Matrix::operator+=(const Matrix &matrix)
{
    assert(rows == matrix.rows && cols == matrix.cols);

    for (size_t i = 0; i < rows * cols; ++i)
        data[i] += matrix.data[i];
}

void Matrix::operator+=(const double value)
{
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] += value;
}

void Matrix::operator-=(const Matrix &matrix)
{
    assert(rows == matrix.rows && cols == matrix.cols);

    for (size_t i = 0; i < rows * cols; ++i)
        data[i] -= matrix.data[i];
}

void Matrix::operator-=(const double value)
{
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] -= value;
}

void Matrix::operator*=(const double value)
{
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] *= value;
}

Matrix operator+(double value, const Matrix &matrix)
{
    return matrix + value;
}

Matrix operator*(double value, const Matrix &matrix)
{
    return matrix * value;
}

Matrix operator*(const VerticalVector &vVector, const Matrix &matrix)
{
    assert(1 == matrix.getRows());
    Matrix result(vVector.getSize(), matrix.getCols());

    for (size_t i = 0; i < vVector.getSize(); ++i)
    {
        for (size_t k = 0; k < matrix.getCols(); ++k)
            result(i, k) = vVector[i] * matrix(0, k);
    }

    return result;
}

Matrix operator*(const HorizontalVector &hVector, const Matrix &matrix)
{
    assert(hVector.getSize() == matrix.getRows());
    Matrix result(1, matrix.getCols());

    for (size_t j = 0; j < matrix.getCols(); ++j)
    {
        result(0, j) = 0;

        for (size_t k = 0; k < matrix.getRows(); ++k)
            result(0, j) += hVector[k] * matrix(j, k);
    }

    return result;
}

size_t Matrix::getRows() const
{
    return rows;
}

size_t Matrix::getCols() const
{
    return cols;
}

Matrix Matrix::transp() const
{
    Matrix result(cols, rows);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            result(j, i) = (*this)(i, j);

    return result;
}

void Matrix::calcDet(const Matrix &matrix, double *val) const
{
    double res = 0;
    assert(matrix.getRows() == matrix.getCols());

    if (matrix.getRows() == 1)
        res = matrix(0, 0);
    else if (matrix.getRows() == 2)
        res = matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
    else
    {
        int k = 1;

        for (size_t i = 0; i < matrix.getCols(); i++)
        {
            Matrix minor;
            minor = matrix.delColRow(0, i);
            double val_minor = 1;
            calcDet(minor, &val_minor);
            res += k * matrix(0, i) * val_minor;
            k = -k;
        }
    }

    *val = res;
}

Matrix Matrix::delColRow(size_t row, size_t col) const
{
    Matrix result(rows - 1, cols - 1);
    size_t i_1 = 0, j_1 = 0;

    for (size_t i = 0; i < rows; i++)
        if (i != row)
        {
            for (size_t j = 0; j < cols; j++)
                if (j != col)
                {
                    result(i_1, j_1) = (*this)(i, j);
                    j_1++;
                }

            i_1++;
            j_1 = 0;
        }

    return result;
}

double Matrix::det() const
{
    double res = 0;
    Matrix::calcDet(*this, &res);

    return res;
}

Matrix Matrix::adj() const
{
    assert(rows == cols);
    Matrix result(rows, cols);

    if (rows == 1)
    {
        result(0, 0) = (*this)(0, 0);
        return result;
    }

    int k;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
        {
            Matrix tmp = delColRow(i, j);
            double val = tmp.det();

            k = ((i + 1 + j + 1) % 2 == 0) ? 1 : -1;
            result(i, j) = k * val;
        }

    return result.transp();
}

Matrix Matrix::inv() const
{
    assert(rows == cols);

    Matrix result(rows, cols);

    if (rows == 1)
    {
        assert(fabs(data[0]) >= 1e-7);
        result(0, 0) = 1 / data[0];

        return result;
    }

    double val = det();
    assert(fabs(data[0]) >= 1e-7);
    result = adj() * (1 / val);

    return result;
}