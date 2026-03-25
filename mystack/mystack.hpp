#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class mystack {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void grow() {
        const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    mystack() : data_(nullptr), size_(0), capacity_(0) {}

    ~mystack() {
        delete[] data_;
    }

    mystack(const mystack& other)
        : data_(other.capacity_ ? new T[other.capacity_] : nullptr),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    mystack(mystack&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    mystack& operator=(const mystack& other) {
        if (this != &other) {
            T* new_data = other.capacity_ ? new T[other.capacity_] : nullptr;
            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
            delete[] data_;
            data_ = new_data;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    mystack& operator=(mystack&& other) noexcept {
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

    void push(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_++] = value;
    }

    void push(T&& value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_++] = std::move(value);
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_++] = T(std::forward<Args>(args)...);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("pop() called on empty mystack");
        }
        --size_;
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("top() called on empty mystack");
        }
        return data_[size_ - 1];
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top() called on empty mystack");
        }
        return data_[size_ - 1];
    }

    bool empty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }
};
