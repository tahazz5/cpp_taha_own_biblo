#pragma once

#include <cassert>
#include <cstddef>
#include <utility>

template <typename T>
class mymatrix {
private:
    T* data_;
    std::size_t rows_;
    std::size_t cols_;

    std::size_t index(std::size_t row, std::size_t col) const noexcept {
        return row * cols_ + col;
    }

public:
    mymatrix() noexcept : data_(nullptr), rows_(0), cols_(0) {}

    mymatrix(std::size_t rows, std::size_t cols)
        : data_((rows && cols) ? new T[rows * cols] : nullptr),
          rows_(rows),
          cols_(cols) {}

    ~mymatrix() {
        delete[] data_;
    }

    mymatrix(const mymatrix& other)
        : data_((other.rows_ && other.cols_) ? new T[other.rows_ * other.cols_] : nullptr),
          rows_(other.rows_),
          cols_(other.cols_) {
        for (std::size_t i = 0; i < rows_ * cols_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    mymatrix(mymatrix&& other) noexcept
        : data_(other.data_), rows_(other.rows_), cols_(other.cols_) {
        other.data_ = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
    }

    mymatrix& operator=(const mymatrix& other) {
        if (this != &other) {
            delete[] data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            if (rows_ && cols_) {
                data_ = new T[rows_ * cols_];
                for (std::size_t i = 0; i < rows_ * cols_; ++i) {
                    data_[i] = other.data_[i];
                }
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }

    mymatrix& operator=(mymatrix&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            other.data_ = nullptr;
            other.rows_ = 0;
            other.cols_ = 0;
        }
        return *this;
    }

    std::size_t rows() const noexcept {
        return rows_;
    }

    std::size_t cols() const noexcept {
        return cols_;
    }

    std::size_t size() const noexcept {
        return rows_ * cols_;
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    T& operator()(std::size_t row, std::size_t col) {
        assert(row < rows_ && col < cols_);
        return data_[index(row, col)];
    }

    const T& operator()(std::size_t row, std::size_t col) const {
        assert(row < rows_ && col < cols_);
        return data_[index(row, col)];
    }

    void fill(const T& value) {
        for (std::size_t i = 0; i < size(); ++i) {
            data_[i] = value;
        }
    }

    bool operator==(const mymatrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            return false;
        }
        for (std::size_t i = 0; i < size(); ++i) {
            if (!(data_[i] == other.data_[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const mymatrix& other) const {
        return !(*this == other);
    }
};
