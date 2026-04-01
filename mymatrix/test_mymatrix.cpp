#include <cassert>
#include <iostream>

#include "mymatrix.hpp"

int main() {
    mymatrix<int> matrix(2, 3);
    assert(matrix.rows() == 2);
    assert(matrix.cols() == 3);
    assert(matrix.size() == 6);

    matrix.fill(5);
    for (std::size_t row = 0; row < matrix.rows(); ++row) {
        for (std::size_t col = 0; col < matrix.cols(); ++col) {
            assert(matrix(row, col) == 5);
        }
    }

    mymatrix<int> copy = matrix;
    assert(copy == matrix);

    mymatrix<int> other(2, 3);
    other(0, 0) = 1;
    other(1, 2) = 9;
    assert(other(0, 0) == 1);
    assert(other(1, 2) == 9);
    assert(other != matrix);

    mymatrix<int> moved = std::move(other);
    assert(moved.rows() == 2);
    assert(moved.cols() == 3);
    assert(moved(0, 0) == 1);
    assert(other.empty());

    mymatrix<int> assigned;
    assigned = moved;
    assert(assigned == moved);

    std::cout << "mymatrix tests passed\n";
    return 0;
}
