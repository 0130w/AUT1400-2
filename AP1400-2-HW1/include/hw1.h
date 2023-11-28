#ifndef AP_HW1_H
#define AP_HW1_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <random>

using Matrix = std::vector<std::vector<double> >;

class algebra {

    public:
        static Matrix zeros(size_t n, size_t m);

        static Matrix ones(size_t n, size_t m);

        static Matrix random(size_t n, size_t m, double min, double max);

        static void show(const Matrix& matrix);

        static Matrix multiply(const Matrix& matrix, double c);

        static Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

        static Matrix sum(const Matrix& matrix, double c);

        static Matrix sum(const Matrix& matrix1, const Matrix& matrix2);

        static Matrix transpose(const Matrix& matrix);

        static Matrix minor(const Matrix& matrix, size_t n, size_t m);

        static double determinant(const Matrix& matrix);

        static Matrix inverse(const Matrix& matrix);

        static Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis = 0);

        static Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);

        static Matrix ero_multiply(const Matrix& matrix, size_t r, double c);

        static Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);

        static Matrix upper_triangular(const Matrix& matrix);
};
#endif //AP_HW1_H
