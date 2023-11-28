#include "hw1.h"

Matrix algebra::zeros(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 0));
}

Matrix algebra::ones(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 1));
}

Matrix algebra::random(size_t n, size_t m, double min, double max) {
    if(min > max) {
        throw std::logic_error(" min number should less than max number");
    }
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(min, max);
    Matrix matrix(n, std::vector<double>(m));
    for(auto &row : matrix) {
        for(auto &elem : row) {
            elem = distribution(generator);
        }
    }
    return matrix;
}

void algebra::show(const Matrix& matrix) {
    std::cout << std::fixed << std::setprecision(3);
    for(auto row : matrix) {
        for(auto element: row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

Matrix algebra::multiply(const Matrix& matrix, double c) {
    Matrix new_matrix = matrix;
    for(auto &row : new_matrix) {
        for(auto &elem : row) {
            elem *= c;
        }
    }
    return new_matrix;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if(matrix1.empty() || matrix2.empty()) {
        if(matrix1.empty() && matrix2.empty()) {
            Matrix matrix;
            return matrix;
        }
        throw std::logic_error("cannot multiply a non-empty matrix with an empty matrix");
    }
    if(matrix1[0].size() != matrix2.size()) {
        throw std::logic_error("cannot multipy two different dimension matrixs");
    }
    int row_num = matrix1.size();
    int column_num = matrix2[0].size();
    int middle_layer = matrix1[0].size();
    Matrix matrix(row_num, std::vector<double>(column_num));
    for(int i = 0; i < row_num; ++i) {
        for(int j = 0; j < column_num; ++j) {
            for(int k = 0; k < middle_layer; ++k) {
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return matrix;
}

Matrix algebra::sum(const Matrix& matrix, double c) {
    Matrix new_matrix = matrix;
    for(auto &row : new_matrix) {
        for(auto &element : row) {
            element += c;
        }
    }
    return new_matrix;
}

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2) {
    if(matrix1.empty() || matrix2.empty()) {
        if(matrix1.empty() && matrix2.empty()) {
            Matrix matrix;
            return matrix;
        }
        throw std::logic_error("cannot add a non-empty matrix with an empty matrix");
    }
    if(matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw std::logic_error("cannot add two different dimension matrixs");
    }
    Matrix new_matrix = matrix1;
    int n = matrix1.size();
    int m = matrix1[0].size();
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            new_matrix[i][j] += matrix2[i][j];
        }
    return new_matrix;
}

Matrix algebra::transpose(const Matrix& matrix) {
    if(matrix.empty()) {
        Matrix matrix;
        return matrix;
    }
    int n = matrix[0].size();
    int m = matrix.size();
    Matrix new_matrix(n, std::vector<double>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}

Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m) {
    int row_num = matrix.size();
    int column_num = matrix[0].size();
    Matrix new_matrix;
    std::vector<double> row;
    for(int i = 0; i < row_num; ++i) {
        if(i == n) continue;
        row.clear();
        for(int j = 0; j < column_num; ++j) {
            if(j == m) continue;
            row.push_back(matrix[i][j]);
        }
        new_matrix.push_back(row);
    }
    return new_matrix;
}

double algebra::determinant(const Matrix& matrix) {
    if(matrix.empty()) { return 1; }
    int row_num = matrix.size();
    int column_num = matrix[0].size();
    if(row_num != column_num) {
        throw std::logic_error("cannot calculate a matrix with different row_num and column_num");
    }
    if(row_num == 1) {
        return matrix[0][0];
    }
    if(row_num == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double result = 0;
    for(int i = 0; i < column_num; ++i) {
        // calculate determinant using the first row
        int sign = i % 2 == 0 ? 1 : -1;
        result += sign * matrix[0][i] * determinant(minor(matrix, 0, i));
    }
    return result;
}

Matrix algebra::inverse(const Matrix& matrix) {
    double matrix_determinant = determinant(matrix);
    if(std::fabs(matrix_determinant) < __DBL_EPSILON__) {
        throw std::logic_error("Matrix with determinant equals to zero doesn't have inverse");
    }
    int row_num = matrix.size();
    Matrix new_matrix = zeros(row_num, row_num);
    for(int i = 0; i < row_num; ++i) {
        for(int j = 0; j < row_num; ++j) {
            int sign = (i + j) % 2 == 0 ? 1 : -1;
            double value = determinant(minor(matrix, i, j));
            new_matrix[i][j] = sign * value / matrix_determinant;
        }
        std::cout << std::endl;
    }
    return transpose(new_matrix);
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
    if(matrix1.empty() || matrix2.empty()) {
        if(matrix1.empty() && matrix2.empty()) {
            Matrix matrix;
            return matrix;
        }
        throw std::logic_error("cannot concatenate a non-empty matrix with an empty matrix");
    }
    Matrix matrix;
    if(axis == 0) {
        if(matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("cannot concatenate two matrix with different column number in axis 0");
        }
        for(auto row : matrix1) matrix.push_back(row);
        for(auto row : matrix2) matrix.push_back(row);
    } else {
        if(matrix1.size() != matrix2.size()) {
            throw std::logic_error("cannot concatenate two matrix with different row number in axis 1");
        }
        matrix.resize(matrix1.size(), std::vector<double>(matrix1[0].size() + matrix2[0].size()));
        for(int i = 0; i < matrix1.size(); ++i) {
            for(int j = 0; j < matrix1[0].size(); ++j) {
                matrix[i][j] = matrix1[i][j];
            }
            for(int j = 0; j < matrix2[0].size(); ++j) {
                matrix[i][j + matrix1[0].size()] = matrix2[i][j];
            }
        }
    }
    return matrix;
}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
    if(matrix.size() - 1 < (r1 < r2 ? r2 : r1)) {
        throw std::logic_error("cannot swap a row whose row_number greater than matrix's size");
    }
    Matrix new_matrix = matrix;
    swap(new_matrix[r1], new_matrix[r2]);
    return new_matrix;
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c) {
    if(matrix.size() - 1 < r) {
        throw std::logic_error("cannot multiply a constant to a non-exist row");
    }
    Matrix new_matrix = matrix;
    for(auto &elem : new_matrix[r])
        elem *= c;
    return new_matrix;
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
    if(matrix.size() - 1 < (r1 < r2 ? r2 : r1)) {
        throw std::logic_error("cannot operate non-exist row");
    }
    Matrix new_matrix = matrix;
    if(matrix.empty()) {
        return new_matrix;
    }
    int m = matrix[0].size();
    for(int i = 0; i < m; ++i) {
        new_matrix[r2][i] += c * matrix[r1][i];
    }
    return new_matrix;
}

Matrix algebra::upper_triangular(const Matrix& matrix) {
    Matrix new_matrix = matrix;
    if(matrix.empty()) { return new_matrix; }
    if(matrix.size() != matrix[0].size()) {
        throw std::logic_error("cannot upper triangular a matrix with different row_num and column_num");
    }
    int n = matrix.size();
    for(int i = 0; i < n - 1; ++i) {
        if(std::fabs(matrix[i][i]) < __DBL_EPSILON__) {
            bool swap_flag = false;
            for(int j = i + 1; j < n; ++j) {
                if(std::fabs(matrix[j][i]) >= __DBL_EPSILON__) {
                    swap(new_matrix[i], new_matrix[j]);
                    swap_flag = true;
                    break;
                }
            }
            if(!swap_flag) {
                continue;
            }
        }
        for(int j = i + 1; j < n; ++j) {
            double row_head = new_matrix[j][i];
            for(int k = i; k < n; ++k) {
                new_matrix[j][k] -= (row_head * new_matrix[i][k] / new_matrix[i][i]);
            }
        }
    }
    return new_matrix;
}