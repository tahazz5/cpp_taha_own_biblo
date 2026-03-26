#pragma once

#include <cstddef>
#include <cstring>
#include <utility>

class mystring {
private:
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

    void grow() {
        const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        char* new_data = new char[new_capacity + 1];
        if (data_) {
            std::strcpy(new_data, data_);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    mystring() : data_(nullptr), size_(0), capacity_(0) {}

    mystring(const char* str) {
        size_ = std::strlen(str);
        capacity_ = size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, str);
    }

    ~mystring() {
        delete[] data_;
    }

    mystring(const mystring& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new char[capacity_ + 1];
        std::strcpy(data_, other.data_);
    }

    mystring(mystring&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    mystring& operator=(const mystring& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new char[capacity_ + 1];
            std::strcpy(data_, other.data_);
        }
        return *this;
    }

    mystring& operator=(mystring&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    char& operator[](std::size_t index) {
        return data_[index];
    }

    const char& operator[](std::size_t index) const {
        return data_[index];
    }

    std::size_t size() const {
        return size_;
    }

    const char* c_str() const {
        return data_ ? data_ : "";
    }

    void append(const char* str) {
        std::size_t len = std::strlen(str);
        while (size_ + len > capacity_) {
            grow();
        }
        std::strcpy(data_ + size_, str);
        size_ += len;
    }
};